#ifndef FIRE_ShaderType_h
#define FIRE_ShaderType_h

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace FIRE
{
enum class ShaderType
{
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

struct ShaderDescriptor
{
    ShaderDescriptor(ShaderType type, std::string code)
        : shaderType(type)
        , shaderCode(std::move(code))
    {
    }

    ShaderDescriptor(ShaderType type, std::filesystem::path path)
        : shaderType(type)
        , filePath(std::move(path))
    {
    }

    ShaderType shaderType;
    std::string shaderCode;
    std::filesystem::path filePath;
};

using Shaders = std::vector<ShaderDescriptor>;

enum class ShaderParameterType
{
    MAT4x4,
    VEC3
};
} // namespace FIRE

#endif