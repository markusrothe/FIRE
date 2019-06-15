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

    Vector3& operator-=(Vector3 const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector3& operator+=(Vector3 const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector3 operator+(Vector3 const& other) const
    {
        Vector3 result = *this;
        result += other;
        return result;
    }

    Vector3 operator-(Vector3 const& other) const
    {
        Vector3 result = *this;
        result -= other;
        return result;
    }

    bool operator==(Vector3 const& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=(Vector3 const& rhs) const
    {
        return !(*this == rhs);
    }

    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};

} // namespace FIRE

#endif
