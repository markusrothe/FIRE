#define GLM_FORCE_CXX17
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <FIRE/Matrix.h>
#include <FIRE/Vertex.h>

namespace FIRE
{
namespace
{
    using array4x4 = std::array<float, 16>;
    array4x4 matToArray(glm::mat4x4 const& mat)
    {
        array4x4 arr;
        auto rawData = glm::value_ptr<float>(mat);
        std::copy(rawData, rawData + arr.max_size(), arr.begin());
        return arr;
    }
} // namespace

class Matrix4x4::Impl
{
public:
    Impl()
        : m_mat(1.0f)
    {
    }

    explicit Impl(array4x4 vals)
        : m_mat(glm::make_mat4x4(vals.data()))
    {
    }

    explicit Impl(glm::mat4x4 const& mat)
        : m_mat(mat)
    {
    }

    bool operator==(Impl const& other) const
    {
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                if(m_mat[j][i] != other.m_mat[j][i])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(Impl const& other) const
    {
        return !(*this == other);
    }

    Impl operator*(Impl const& other) const
    {
        return Impl(m_mat * other.m_mat);
    }

    Impl& operator*=(Impl const& other)
    {
        m_mat *= other.m_mat;
        return *this;
    }

    float At(int column, int row) const
    {
        return m_mat[column][row];
    }

    array4x4 Raw() const
    {
        return matToArray(m_mat);
    }

private:
    glm::mat4x4 m_mat;
};

Matrix4x4 Matrix4x4::identity;

Matrix4x4::Matrix4x4()
    : m_impl(std::make_unique<Matrix4x4::Impl>())
{
}

Matrix4x4::Matrix4x4(array4x4 vals)
    : m_impl(std::make_unique<Matrix4x4::Impl>(std::move(vals)))
{
}

Matrix4x4::~Matrix4x4() = default;

Matrix4x4::Matrix4x4(Matrix4x4 const& other)
    : m_impl(std::make_unique<Matrix4x4::Impl>(other.Raw()))
{
}

Matrix4x4::Matrix4x4(Impl impl)
    : m_impl(std::make_unique<Matrix4x4::Impl>(impl))
{
}

Matrix4x4& Matrix4x4::operator=(Matrix4x4 const& other)
{
    m_impl.reset();
    m_impl = std::make_unique<Matrix4x4::Impl>(other.Raw());

    return *this;
}

bool Matrix4x4::operator==(Matrix4x4 const& other) const
{
    return *m_impl == *other.m_impl;
}

bool Matrix4x4::operator!=(Matrix4x4 const& other) const
{
    return *m_impl != *other.m_impl;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 const& other) const
{
    return Matrix4x4((*m_impl) * (*other.m_impl));
}

Matrix4x4& Matrix4x4::operator*=(Matrix4x4 const& other)
{
    *this = *this * other;
    return *this;
}

float Matrix4x4::At(int column, int row) const
{
    return m_impl->At(column, row);
}

array4x4 Matrix4x4::Raw() const
{
    return m_impl->Raw();
}

Matrix4x4 CreateViewMatrix(Vertex const& pos, Vertex const& lookAt, Vertex const& up)
{
    glm::vec3 const posVec(pos.x, pos.y, pos.z);
    glm::vec3 const lookAtVec(lookAt.x, lookAt.y, lookAt.z);
    glm::vec3 const upVec(up.x, up.y, up.z);
    return Matrix4x4(matToArray(glm::lookAt(posVec, lookAtVec, upVec)));
}

Matrix4x4 CreatePerspectiveMatrix(float fovy, float aspect, float near, float far)
{
    return Matrix4x4(matToArray(glm::perspective(fovy, aspect, near, far)));
}

} // namespace FIRE