#ifndef fire_defaultmaterialfactory_h
#define fire_defaultmaterialfactory_h

#include <memory>

namespace Fire
{
class Material;
std::unique_ptr<Material> CreateDefaultMaterial();
} // namespace Fire

#endif // fire_defaultmaterialfactory_h