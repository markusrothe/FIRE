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
aiScene const* GetSceneFromFileContent(Assimp::Importer& importer, std::string const& fileContent)
{
    return importer.ReadFileFromMemory(
        fileContent.c_str(),
        fileContent.length(),
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
}

aiScene const* GetSceneFromFile(Assimp::Importer& importer, std::string const& filepath)
{
    return importer.ReadFile(
        filepath.c_str(),
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
}

void ProcessVertices(aiMesh const* mesh, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs)
{
    positions.reserve(mesh->mNumVertices);
    normals.reserve(mesh->mNumVertices);
    uvs.reserve(mesh->mNumVertices);
    for(auto j = 0u; j < mesh->mNumVertices; ++j)
    {
        auto const& pos = mesh->mVertices[j];
        positions.emplace_back(pos.x, pos.y, pos.z);

        auto const& normal = mesh->mNormals[j];
        normals.emplace_back(normal.x, normal.y, normal.z);

        if(mesh->HasTextureCoords(0))
        {
            auto const& uv = mesh->mTextureCoords[0][j]; //right now we only care about one set of uvs per vertex
            uvs.emplace_back(uv.x, uv.y);
        }
    }
}

void ProcessIndices(aiMesh const* mesh, std::vector<unsigned int>& indices)
{
    indices.reserve(mesh->mNumFaces * 3);
    for(auto j = 0u; j < mesh->mNumFaces; ++j)
    {
        auto const& face = mesh->mFaces[j];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }
}

void ProcessMesh(
    aiMesh const* mesh,
    std::vector<glm::vec3>& positions,
    std::vector<glm::vec3>& normals,
    std::vector<glm::vec2>& uvs,
    std::vector<unsigned int>& indices)
{
    ProcessVertices(mesh, positions, normals, uvs);
    ProcessIndices(mesh, indices);
}

std::vector<Texture2D*> ProcessTextures(aiScene const* scene, TextureManager& texManager)
{
    std::vector<Texture2D*> textures;
    textures.resize(scene->mNumMaterials);
    for(unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        const aiMaterial* pMaterial = scene->mMaterials[i];
        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;
            aiTextureMapMode mapMode;
            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, nullptr, nullptr, nullptr, nullptr, &mapMode) == AI_SUCCESS)
            {
                // ... process data if not NULL ...
                // ... x = width, y = height, n = # 8-bit components per pixel ...
                // ... replace '0' with '1'..'4' to force that many components per pixel
                // ... but 'n' will always be the number that it would have been if you said 0
                std::string fullPath{std::string("./") + Path.data};
                int width, height, numComponents;
                unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &numComponents, 0);
                if(data)
                {
                    std::vector<uint8_t> pixels(data, data + (height * width * numComponents));
                    stbi_image_free(data);
                    Texture2D::WrappingMode wrapping = Texture2D::WrappingMode::WRAP;
                    switch(mapMode)
                    {
                    case aiTextureMapMode_Clamp:
                        wrapping = Texture2D::WrappingMode::CLAMP;
                        break;
                    case aiTextureMapMode_Mirror:
                        wrapping = Texture2D::WrappingMode::MIRROR;
                        break;
                    case aiTextureMapMode_Wrap:
                    case aiTextureMapMode_Decal:
                    case _aiTextureMapMode_Force32Bit:
                        wrapping = Texture2D::WrappingMode ::WRAP;
                        break;
                    }

                    textures[i] = texManager.CreateImageTexture(Path.data, width, height, pixels, static_cast<uint8_t>(numComponents), wrapping, Texture2D::Filter::LINEAR);
                }
            }
        }
    }
    return textures;
}

std::vector<Renderable> CreateRenderables(
    aiScene const* scene,
    FIRE::MeshManager& meshManager,
    TextureManager& texManager,
    FIRE::Material const& material)
{
    std::vector<Renderable> renderables;
    renderables.reserve(scene->mNumMeshes);
    std::vector<Texture2D*> textures = ProcessTextures(scene, texManager);

    int c = 0;
    for(auto i = 0u; i < scene->mNumMeshes; ++i)
    {
        std::vector<glm::vec3> positions, normals;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> indices;
        auto mesh = scene->mMeshes[i];

        auto matIndex = mesh->mMaterialIndex;
        ProcessMesh(mesh, positions, normals, uvs, indices);

        std::stringstream ss_mesh, ss_renderable;
        ss_mesh << "mesh_" << c;
        ss_renderable << "renderable_" << c;
        c++;

        Renderable renderable;
        renderable.mesh = meshManager.Create(
            FIRE::MeshCategory::Custom,
            FIRE::MeshPrimitives::Triangles,
            ss_mesh.str(),
            std::move(positions),
            std::move(normals),
            std::move(uvs),
            std::move(indices));
        renderable.name = ss_renderable.str();
        renderable.material = material;
        if(textures[matIndex])
        {
            renderable.material.AddTexture(textures[matIndex], 0u);
        }

        renderables.push_back(renderable);
    }
    return renderables;
}
} // namespace

ModelLoader::ModelLoader(MeshManager& meshManager, TextureManager& texManager)
    : m_meshManager(meshManager)
    , m_texManager(texManager)
{
}

std::vector<Renderable> ModelLoader::Load(std::string const& fileContent, FIRE::Material const& material)
{
    Assimp::Importer importer;
    return CreateRenderables(GetSceneFromFileContent(importer, fileContent), m_meshManager, m_texManager, material);
}

std::vector<Renderable> ModelLoader::LoadFromFile(std::string const& filepath, FIRE::Material const& material)
{
    Assimp::Importer importer;
    return CreateRenderables(GetSceneFromFile(importer, filepath), m_meshManager, m_texManager, material);
}

} // namespace FIRE
