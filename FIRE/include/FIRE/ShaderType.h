#ifndef FIRE_ShaderType_h
#define FIRE_ShaderType_h

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

using Shaders = std::vector<std::pair<ShaderType, std::string>>;

enum class ShaderParameterType
{
    MAT4x4,
    VEC3

};
} // namespace FIRE

#endif