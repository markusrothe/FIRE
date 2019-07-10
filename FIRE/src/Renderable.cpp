#include <FIRE/Renderable.h>
#include <FIRE/Transform.h>
#include <cassert>
#include <utility>
namespace FIRE
{
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
