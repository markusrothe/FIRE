#include "MeshFactory.h"
#include "ModelLoader.h"
#include "TextureFactory.h"
#include <FIRE/AssetFacade.h>
#include <ShaderFactory.h>
#include <fstream>
#include <utility>

namespace FIRE
{
namespace
{
std::string GetFileContent(std::filesystem::path const& filePath)
{
    std::ifstream file(filePath);
    return std::string{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
}
} // namespace

AssetFacade::AssetFacade(
    std::unique_ptr<TextureFactory> texFactory,
    std::unique_ptr<ShaderFactory> shaderFactory)
    : m_texFactory(std::move(texFactory))
    , m_shaderFactory(std::move(shaderFactory))
{
    m_materials["Default"] = Material("Default", m_shaderFactory->CreateDefaultShader());
    m_materials["TextDefault"] = Material("TextDefault", m_shaderFactory->CreateDefaultTextShader());
}

AssetFacade::~AssetFacade() = default;

void AssetFacade::SubmitTexture(std::string const& name, std::string const& textureFilePath, Texture2D::WrappingMode wrappingMode)
{
    if(m_textures.find(name) == m_textures.end())
    {
        m_textures[name] = m_texFactory->Load(textureFilePath, wrappingMode);
    }
}

void AssetFacade::SubmitTexture(std::string const& name, std::unique_ptr<Texture2D> texture)
{
    if(m_textures.find(name) == m_textures.end())
    {
        m_textures[name] = std::move(texture);
    }
}

Texture2D* AssetFacade::GetTexture(std::string const& name) const
{
    if(auto const textureIter = m_textures.find(name); textureIter != m_textures.cend())
    {
        return textureIter->second.get();
    }

    return nullptr;
}

void AssetFacade::SubmitTexture(
    std::string const& name,
    uint32_t width,
    uint32_t height,
    std::vector<uint8_t> const& data,
    uint8_t numComponents,
    Texture2D::WrappingMode wrappingMode,
    Texture2D::Filter filter)
{
    if(m_textures.find(name) != m_textures.end())
    {
        throw std::runtime_error("A texture with that name already exists.");
    }

    m_textures[name] = m_texFactory->Create2DTexture(width, height, data, numComponents, wrappingMode, filter);
}

FontCharacter AssetFacade::CreateFontCharacter(char c)
{
    auto fontCharIter = m_fontCharacters.find(c);
    if(fontCharIter == m_fontCharacters.end())
    {
        auto fontChar = m_texFactory->LoadFontCharacter(c);

        auto const textureName = std::string("fontChar_") + c;
        m_textures[textureName] = m_texFactory->Create2DTexture(
            fontChar.size.x, fontChar.size.y, fontChar.data, 1, Texture2D::WrappingMode::CLAMP,
            Texture2D::Filter::NEAREST);
        fontChar.texture = m_textures[textureName].get();
        m_fontCharacters.insert(std::make_pair(c, fontChar));
        return fontChar;
    }

    return fontCharIter->second;
}
void AssetFacade::SubmitShaders(std::string const& name, Shaders const& shaders)
{
    if(m_materials.find(name) == m_materials.end())
    {
        m_materials[name] = Material(name, m_shaderFactory->Create(shaders));
    }
}

void AssetFacade::SubmitShadersFromFiles(std::string const& name, Shaders const& shaders)
{
    Shaders cpy = shaders;
    for(auto& shader : cpy)
    {
        shader.shaderCode = GetFileContent(shader.filePath);
    }
    SubmitShaders(name, cpy);
}

Material AssetFacade::GetMaterial(std::string const& name) const
{
    if(auto it = m_materials.find(name); it != m_materials.end())
    {
        return it->second;
    }

    return Material();
}

void AssetFacade::SubmitModel(std::string const& name, std::string const& fileContent)
{
    ModelLoader loader(ModelLoader::Source::Memory, fileContent);
    ProcessModel(name, loader);
}

void AssetFacade::SubmitModelFromFile(std::string const& name, std::string const& filePath)
{
    ModelLoader loader(ModelLoader::Source::File, filePath);
    ProcessModel(name, loader);
}

void AssetFacade::ProcessModel(std::string const& name, ModelLoader& loader)
{
    Foo foo;
    foo.name = name;

    auto numModels = loader.GetNumModels();
    for(auto i = 0u; i < numModels; ++i)
    {
        auto model = loader.StealModel(0u); // always take the first index as numModels shrinks with every iteration.
        auto const meshName = model.mesh->Name();
        SubmitMesh(meshName, std::move(model.mesh));
        foo.meshes.push_back(meshName);

        if(!model.texturePath.empty())
        {
            std::string fullPath{std::string("./") + model.texturePath};
            SubmitTexture(model.texturePath, fullPath, model.textureWrapping);
            foo.textures.push_back(model.texturePath);
        }
        else
        {
            foo.textures.emplace_back("");
        }
    }

    m_models[foo.name] = foo;
}

std::vector<Mesh3D*> AssetFacade::GetModelMeshes(std::string const& name) const
{
    std::vector<Mesh3D*> meshes;
    if(auto it = m_models.find(name); it != m_models.end())
    {
        for(auto& meshName : it->second.meshes)
        {
            auto meshIt = m_meshes.find(meshName);
            if(meshIt != std::end(m_meshes))
            {
                meshes.push_back(meshIt->second.get());
            }
        }
    }

    return meshes;
}

void AssetFacade::SubmitMesh(std::string const& name, std::unique_ptr<Mesh3D> mesh)
{
    if(m_meshes.find(name) == m_meshes.end())
    {
        auto meshPtr = mesh.get();
        m_meshes[name] = std::move(mesh);
        meshPtr->GetVertexDeclaration().AddSection("vPos", 3u, 0u);
        meshPtr->GetVertexDeclaration().AddSection("vNormal", 3u, static_cast<uint32_t>(meshPtr->Positions().size() * sizeof(float) * 3));
        meshPtr->GetVertexDeclaration().AddSection("vUV", 2u, static_cast<uint32_t>((meshPtr->Positions().size() + meshPtr->Normals().size()) * sizeof(float) * 3));
    }
}

Mesh3D* AssetFacade::GetMesh(std::string const& name) const
{
    if(auto it = m_meshes.find(name); it != m_meshes.end())
    {
        return it->second.get();
    }

    return nullptr;
}

void AssetFacade::CreateMesh(std::string const& name, MeshCategory meshCategory)
{
    if(m_meshes.find(name) != m_meshes.end())
    {
        throw std::runtime_error("A Mesh with that name already exists");
    }

    switch(meshCategory)
    {
    case MeshCategory::Plane:
        m_meshes[name] = MeshFactory::CreatePlane(name);
        break;
    case MeshCategory::Cube:
        m_meshes[name] = MeshFactory::CreateCube(name);
        break;
    case MeshCategory::Sphere:
        m_meshes[name] = MeshFactory::CreateSphere(name, 20u);
        break;
    case MeshCategory::LineGrid:
        m_meshes[name] = MeshFactory::CreateLineGrid(name, 100u, 100u);
        break;
    case MeshCategory::TriangleGrid:
        m_meshes[name] = MeshFactory::CreateTriangleGrid(name, 100u, 100u);
        break;
    case MeshCategory::Custom:
        break;
    }
}

RenderableBuilder AssetFacade::CreateRenderables(std::string const& namePrefix, uint32_t count)
{
    return RenderableBuilder(*this, namePrefix, count);
}

std::vector<Renderable> AssetFacade::CreateModelRenderables(std::string const& namePrefix, std::string const& modelName, std::string const& overrideMaterial)
{
    auto model = m_models.find(modelName);
    if(model == m_models.end())
    {
        return {};
    }

    auto& meshes = model->second.meshes;
    auto& textures = model->second.textures;
    auto const numMeshes = static_cast<uint32_t>(model->second.meshes.size());
    auto builder = CreateRenderables(namePrefix, numMeshes);
    for(auto i = 0u; i < numMeshes; ++i)
    {
        builder.WithMesh(meshes[i])
            .WithMaterial(overrideMaterial)
            .WithTexture(textures[i], 0u);
    }

    return builder.Build();
}

OverlayBuilder AssetFacade::CreateTextOverlays(std::string const& namePrefix, uint32_t count)
{
    return OverlayBuilder(*this, namePrefix, count);
}

} // namespace FIRE
