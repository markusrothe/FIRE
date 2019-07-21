#include <FIRE/Renderable.h>
#include <FIRE/Transform.h>
#include <cassert>
#include <utility>
namespace FIRE
{
Renderable::Renderable(std::string name, Material mat, MeshHandle mesh)
    : name(std::move(name))
    , material(std::move(mat))
    , mesh(std::move(mesh))
{
}

bool operator==(Renderable const& lhs, Renderable const& rhs)
{
    return lhs.name == rhs.name;
}

bool operator!=(Renderable const& lhs, Renderable const& rhs)
{
    return !(lhs == rhs);
}

bool operator<(Renderable const& lhs, Renderable const& rhs)
{
    return lhs.name < rhs.name;
}

} // namespace FIRE
