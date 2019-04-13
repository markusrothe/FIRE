#ifndef FIRE_Vector_h
#define FIRE_Vector_h

namespace FIRE
{
struct Vector3
{
    Vector3() = default;

    Vector3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    bool operator==(Vector3 const& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=(Vector3 const& rhs) const
    {
        return !(*this == rhs);
    }

    float x, y, z;
};
} // namespace FIRE

#endif
