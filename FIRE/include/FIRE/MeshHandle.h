#ifndef FIRE_MeshHandle_h
#define FIRE_MeshHandle_h

#include <FIRE/MeshType.h>
#include <string>

namespace FIRE
{
struct MeshHandle
{
    MeshHandle() = default;

    MeshHandle(std::string name, MeshCategory category, MeshPrimitives primitives)
        : name(std::move(name))
        , type({category, primitives})
    {
    }

    std::string name;
    MeshType type;
};
} // namespace FIRE

#endif // FIRE_MeshHandle_h