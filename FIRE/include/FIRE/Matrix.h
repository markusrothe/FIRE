#ifndef FIRE_Matrix_h
#define FIRE_Matrix_h

#include <array>
#include <memory>
namespace FIRE
{
struct Vector3;
class Matrix4x4
{
public:
    static Matrix4x4 identity;

    Matrix4x4();
    explicit Matrix4x4(std::array<float, 16> vals);

    ~Matrix4x4();

    Matrix4x4(Matrix4x4 const& other);
    Matrix4x4& operator=(Matrix4x4 const& other);

    bool operator==(Matrix4x4 const& other) const;
    bool operator!=(Matrix4x4 const& other) const;

    Matrix4x4 operator*(Matrix4x4 const& other) const;
    Matrix4x4& operator*=(Matrix4x4 const& other);

    float At(int column, int row) const;
    std::array<float, 16> Raw() const;

private:
    class Impl;

    explicit Matrix4x4(Impl impl);

    std::unique_ptr<Impl> m_impl;
};

Matrix4x4 CreateViewMatrix(Vector3 const& pos, Vector3 const& lookAt, Vector3 const& up);
Matrix4x4 CreatePerspectiveMatrix(float fovy, float aspect, float near, float far);

} // namespace FIRE

#endif // !FIRE_Matrix_h
