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

    float x, y, z;
};
} // namespace FIRE

#endif
