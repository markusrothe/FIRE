#ifndef fire_materialfactory_h
#define fire_materialfactory_h

#include <memory>
#include <string>

namespace Fire
{
class Material;

std::unique_ptr<Material> CreateMaterial(
    std::string const& materialName, std::string const& vertexShaderCode,
    std::string const& fragmentShaderCode);

} // namespace Fire

#endif
