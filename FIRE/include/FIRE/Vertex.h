#ifndef FIRE_Vertex_h
#define FIRE_Vertex_h

namespace FIRE
{
struct Vertex
{
    Vertex() = default;

    Vertex(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    bool operator==(Vertex const& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=(Vertex const& rhs) const
    {
        return !(*this == rhs);
    }

    float x, y, z;
};
} // namespace FIRE

#endif
