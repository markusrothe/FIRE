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

//
//void ProcessMesh(
//    aiMesh const* mesh,
//    std::vector<glm::vec3>& positions,
//    std::vector<glm::vec3>& normals,
//    std::vector<glm::vec2>& uvs,
//    std::vector<unsigned int>& indices)
//{
//    ProcessVertices(mesh, positions, normals, uvs);
//    ProcessIndices(mesh, indices);
//}
//
//std::vector<Texture2D*> ProcessTextures(aiScene const* scene, TextureManager& texManager)
//{
//    std::vector<Texture2D*> textures;
//    textures.resize(scene->mNumMaterials);
//    for(unsigned int i = 0; i < scene->mNumMaterials; i++)
//    {
//        const aiMaterial* pMaterial = scene->mMaterials[i];
//        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
//        {
//            aiString Path;
//            aiTextureMapMode mapMode;
//            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, nullptr, nullptr, nullptr, nullptr, &mapMode) == AI_SUCCESS)
//            {
//                // ... process data if not NULL ...
//                // ... x = width, y = height, n = # 8-bit components per pixel ...
//                // ... replace '0' with '1'..'4' to force that many components per pixel
//                // ... but 'n' will always be the number that it would have been if you said 0
//                std::string fullPath{std::string("./") + Path.data};
//                int width, height, numComponents;
//                unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &numComponents, 0);
//                if(data)
//                {
//                    std::vector<uint8_t> pixels(data, data + (height * width * numComponents));
//                    stbi_image_free(data);
//                    Texture2D::WrappingMode wrapping = Texture2D::WrappingMode::WRAP;
//                    switch(mapMode)
//                    {
//                    case aiTextureMapMode_Clamp:
//                        wrapping = Texture2D::WrappingMode::CLAMP;
//                        break;
//                    case aiTextureMapMode_Mirror:
//                        wrapping = Texture2D::WrappingMode::MIRROR;
//                        break;
//                    case aiTextureMapMode_Wrap:
//                    case aiTextureMapMode_Decal:
//                    case _aiTextureMapMode_Force32Bit:
//                        wrapping = Texture2D::WrappingMode ::WRAP;
//                        break;
//                    }
//
//                    textures[i] = texManager.CreateImageTexture(Path.data, width, height, pixels, static_cast<uint8_t>(numComponents), wrapping, Texture2D::Filter::LINEAR);
//                }
//            }
//        }
//    }
//    return textures;
//}
//
//std::vector<Renderable> CreateRenderables(
//    aiScene const* scene,
//    FIRE::MeshManager& meshManager,
//    TextureManager& texManager,
//    FIRE::Material const& material)
//{
//    std::vector<Renderable> renderables;
//    renderables.reserve(scene->mNumMeshes);
//    std::vector<Texture2D*> textures = ProcessTextures(scene, texManager);
//
//    int c = 0;
//    for(auto i = 0u; i < scene->mNumMeshes; ++i)
//    {
//        std::vector<glm::vec3> positions, normals;
//        std::vector<glm::vec2> uvs;
//        std::vector<unsigned int> indices;
//        auto mesh = scene->mMeshes[i];
//
//        auto matIndex = mesh->mMaterialIndex;
//        ProcessMesh(mesh, positions, normals, uvs, indices);
//
//        std::stringstream ss_mesh, ss_renderable;
//        ss_mesh << "mesh_" << c;
//        ss_renderable << "renderable_" << c;
//        c++;
//
//        Renderable renderable;
//        renderable.mesh = meshManager.Create(
//            FIRE::MeshCategory::Custom,
//            FIRE::MeshPrimitives::Triangles,
//            ss_mesh.str(),
//            std::move(positions),
//            std::move(normals),
//            std::move(uvs),
//            std::move(indices));
//        renderable.name = ss_renderable.str();
//        renderable.material = material;
//        if(textures[matIndex])
//        {
//            renderable.material.AddTexture(textures[matIndex], 0u);
//        }
//
//        renderables.push_back(renderable);
//    }
//    return renderables;
//}

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

} // namespace FIRE
