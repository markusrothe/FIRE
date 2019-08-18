#include <FIRE/Message.h>
#include <FIRE/Renderable.h>
#include <utility>
namespace FIRE
{
Renderable::Renderable(std::string name, Material mat, Mesh3D* mesh)
    : name(std::move(name))
    , material(std::move(mat))
    , mesh(mesh)
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
