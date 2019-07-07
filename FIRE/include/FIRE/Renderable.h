#ifndef FIRE_Renderable_h
#define FIRE_Renderable_h

#include <FIRE/Material.h>
#include <FIRE/MeshHandle.h>
#include <FIRE/Transform.h>
#include <string>

namespace FIRE
{

struct Renderable
{
    std::string name;
    Transform transform;
    Material material;
    MeshHandle mesh;
};

bool operator==(Renderable const& lhs, Renderable const& rhs);
bool operator!=(Renderable const& lhs, Renderable const& rhs);

} // namespace FIRE

#endif // FIRE_Renderable_h
