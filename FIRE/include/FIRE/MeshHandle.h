#ifndef FIRE_MeshHandle_h
#define FIRE_MeshHandle_h

#include <FIRE/MeshType.h>
#include <string>

namespace FIRE
{
struct MeshHandle
{
    std::string name;
    MeshType type;
};
} // namespace FIRE

#endif // FIRE_MeshHandle_h