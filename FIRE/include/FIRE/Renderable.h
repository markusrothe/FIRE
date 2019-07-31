#ifndef FIRE_Renderable_h
#define FIRE_Renderable_h

#include <FIRE/Material.h>
#include <FIRE/Mesh3D.h>
#include <FIRE/Transform.h>
#include <string>

namespace FIRE
{

struct Renderable
{
    Renderable() = default;
    Renderable(std::string name, Material mat, Mesh3D* mesh);

    std::string name;
    Material material;
    Mesh3D* mesh{};
};

bool operator==(Renderable const& lhs, Renderable const& rhs);
bool operator!=(Renderable const& lhs, Renderable const& rhs);
bool operator<(Renderable const& lhs, Renderable const& rhs);

} // namespace FIRE

#endif // FIRE_Renderable_h
