#include <FIRE/MeshManager.h>
#include <FIRE/ModelLoader.h>
#include <FIRE/TextureManager.h>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace FIRE
{

namespace
{
aiScene const* GetScene(Assimp::Importer& importer, ModelLoader::Source source, std::string const& str)
{
    auto const flags =
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices;

    return source == ModelLoader::Source::Memory
               ? importer.ReadFileFromMemory(str.c_str(), str.length(), flags)
               : importer.ReadFile(str.c_str(), flags);
}

void ProcessVertices(aiMesh const* mesh, Mesh3D& target)
{
    assert(mesh);
    for(auto j = 0u; j < mesh->mNumVertices; ++j)
    {
        auto const& pos = mesh->mVertices[j];
        target.AddPosition({pos.x, pos.y, pos.z});

        auto const& normal = mesh->mNormals[j];
        target.AddNormal({normal.x, normal.y, normal.z});

        //right now we only care about one set of uvs per vertex
        if(mesh->HasTextureCoords(0))
        {
            auto const& uv = mesh->mTextureCoords[0][j];
            target.AddUV({uv.x, uv.y});
        }
    }
}

void ProcessIndices(aiMesh const* mesh, Mesh3D& target)
{
    for(auto j = 0u; j < mesh->mNumFaces; ++j)
    {
        auto const& face = mesh->mFaces[j];
        target.AddIndices({face.mIndices[0], face.mIndices[1], face.mIndices[2]});
    }
}

void ProcessMaterial(aiMaterial const* material, std::pair<std::string, Texture2D::WrappingMode>& target)
{
    if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString path;
        aiTextureMapMode mapMode;
        if(material->GetTexture(
               aiTextureType_DIFFUSE, 0, &path,
               nullptr, nullptr, nullptr, nullptr, &mapMode) == AI_SUCCESS)
        {
            target.first = std::string(path.data);
            switch(mapMode)
            {
            case aiTextureMapMode_Clamp:
                target.second = Texture2D::WrappingMode::CLAMP;
                break;
            case aiTextureMapMode_Mirror:
                target.second = Texture2D::WrappingMode::MIRROR;
                break;
            case aiTextureMapMode_Wrap:
            case aiTextureMapMode_Decal:
            case _aiTextureMapMode_Force32Bit:
                target.second = Texture2D::WrappingMode ::WRAP;
                break;
            }

            // ... process data if not NULL ...
            // ... x = width, y = height, n = # 8-bit components per pixel ...
            // ... replace '0' with '1'..'4' to force that many components per pixel
            // ... but 'n' will always be the number that it would have been if you said 0
            //            std::string fullPath{std::string("./") + Path.data};
            //            int width, height, numComponents;
            //            unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &numComponents, 0);
            //            if(data)
            //            {
            //                std::vector<uint8_t> pixels(data, data + (height * width * numComponents));
            //                stbi_image_free(data);
            //            textures[i] = texManager.CreateImageTexture(Path.data, width, height, pixels, static_cast<uint8_t>(numComponents), wrapping, Texture2D::Filter::LINEAR);
        }
    }
}
} // namespace

ModelLoader::ModelLoader(Source source, std::string const& str)
{
    Assimp::Importer importer;
    auto scene = GetScene(importer, source, str);
    for(auto i = 0u; i < scene->mNumMeshes; ++i)
    {
        std::stringstream ss;
        ss << "mesh" << i;
        auto mesh = std::make_unique<Mesh3D>(
            ss.str(), MeshType(MeshCategory::Custom, MeshPrimitives::Triangles));

        ProcessVertices(scene->mMeshes[i], *mesh);
        ProcessIndices(scene->mMeshes[i], *mesh);
        m_meshes.push_back(std::move(mesh));
    }

    m_textures.resize(2u);
    for(auto i = 0u; i < scene->mNumMaterials; ++i)
    {
        std::pair<std::string, Texture2D::WrappingMode> target;
        ProcessMaterial(scene->mMaterials[i], target);
        m_textures.push_back(target);
    }
}

std::vector<glm::vec3> ModelLoader::GetPositions(uint32_t meshIndex) const
{
    CheckMeshIndex(meshIndex);
    return m_meshes[meshIndex]->Positions();
}

std::vector<glm::vec3> ModelLoader::GetNormals(uint32_t meshIndex) const
{
    CheckMeshIndex(meshIndex);
    return m_meshes[meshIndex]->Normals();
}

std::vector<glm::vec2> ModelLoader::GetTextureCoordinates(uint32_t meshIndex) const
{
    CheckMeshIndex(meshIndex);
    return m_meshes[meshIndex]->UVs();
}

std::vector<uint32_t> ModelLoader::GetIndices(uint32_t meshIndex) const
{
    CheckMeshIndex(meshIndex);
    return m_meshes[meshIndex]->Indices();
}

uint32_t ModelLoader::GetNumMeshes() const
{
    return m_meshes.size();
}

void ModelLoader::CheckMeshIndex(uint32_t meshIndex) const
{
    if(meshIndex >= GetNumMeshes())
    {
        throw std::runtime_error("Invalid meshIndex");
    }
}
std::string ModelLoader::GetTexture(uint32_t meshIndex) const
{
    CheckMeshIndex(meshIndex);
    return m_textures[meshIndex].first;
}

} // namespace FIRE
