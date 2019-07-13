#ifndef FIRE_MeshType_h
#define FIRE_MeshType_h

namespace FIRE
{
enum class MeshCategory
{
    Plane,
    Cube,
    Sphere,
    LineGrid,
    Custom
};

enum class MeshPrimitives
{
    Points,
    Lines,
    Triangles
};

struct MeshType
{
    MeshType() = default;

    MeshType(MeshCategory category, MeshPrimitives primitives)
        : category(category)
        , primitives(primitives)
    {
    }

    MeshCategory category;
    MeshPrimitives primitives;

    bool operator==(MeshType const& other) const
    {
        return category == other.category && primitives == other.primitives;
    }

    bool operator!=(MeshType const& other) const
    {
        return !(*this == other);
    }
};

} // namespace FIRE

#endif // FIRE_MeshType_h