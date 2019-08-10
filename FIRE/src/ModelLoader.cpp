#include <FIRE/Mesh3D.h>
#include <ModelLoader.h>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <sstream>

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
        }
    }
}
} // namespace

ModelLoader::ModelLoader(Source source, std::string const& str)
{
    Assimp::Importer importer;
    auto scene = GetScene(importer, source, str);

    std::vector<std::pair<std::string, Texture2D::WrappingMode>> textures;
    textures.resize(scene->mNumMaterials);
    for(auto i = 0u; i < scene->mNumMaterials; ++i)
    {
        std::pair<std::string, Texture2D::WrappingMode> target;
        ProcessMaterial(scene->mMaterials[i], target);
        textures[i] = target;
    }

    for(auto i = 0u; i < scene->mNumMeshes; ++i)
    {
        std::stringstream ss;
        ss << "mesh" << i;
        auto mesh = std::make_unique<Mesh3D>(
            ss.str(), MeshType(MeshCategory::Custom, MeshPrimitives::Triangles));

        ProcessVertices(scene->mMeshes[i], *mesh);
        ProcessIndices(scene->mMeshes[i], *mesh);
        auto const matIndex = scene->mMeshes[i]->mMaterialIndex;
        m_models.push_back({std::move(mesh), textures[matIndex].first, textures[matIndex].second});
    }
}

std::pair<std::string, Texture2D::WrappingMode> ModelLoader::GetTexture(uint32_t modelIndex) const
{
    CheckMeshIndex(modelIndex);
    return std::make_pair(m_models[modelIndex].texturePath, m_models[modelIndex].textureWrapping);
}

uint32_t ModelLoader::GetNumModels() const
{
    return static_cast<uint32_t>(m_models.size());
}

void ModelLoader::CheckMeshIndex(uint32_t modelIndex) const
{
    if(modelIndex >= GetNumModels())
    {
        throw std::runtime_error("Invalid modelIndex");
    }
}

Model const& ModelLoader::GetModel(uint32_t modelIndex) const
{
    CheckMeshIndex(modelIndex);
    return m_models[modelIndex];
}

Model ModelLoader::StealModel(uint32_t modelIndex)
{
    CheckMeshIndex(modelIndex);
    auto stolenModel = std::move(m_models[modelIndex]);
    m_models.erase(std::begin(m_models) + modelIndex);
    return stolenModel;
}

} // namespace FIRE
