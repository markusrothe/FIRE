#define GLM_FORCE_CXX17
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <FIRE/Matrix.h>

namespace FIRE
{

class Matrix4x4::Impl
{
public:
    Impl()
        : m_mat(1.0f)
    {
    }
    
    explicit Impl(std::array<float, 16> vals)
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
                if (m_mat[j][i] != other.m_mat[j][i])
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

    std::array<float, 16> Raw() const
    {
        // column major
        std::array<float, 16> vals{
            m_mat[0][0],
            m_mat[0][1],
            m_mat[0][2],
            m_mat[0][3],
            m_mat[1][0],
            m_mat[1][1],
            m_mat[1][2],
            m_mat[1][3],
            m_mat[2][0],
            m_mat[2][1],
            m_mat[2][2],
            m_mat[2][3],
            m_mat[3][0],
            m_mat[3][1],
            m_mat[3][2],
            m_mat[3][3],
        };

        return vals;
    }

private:
    glm::mat4x4 m_mat;
};

Matrix4x4 Matrix4x4::identity;

Matrix4x4::Matrix4x4()
    : m_impl(std::make_unique<Matrix4x4::Impl>())
{
}

Matrix4x4::Matrix4x4(std::array<float, 16> vals)
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

std::array<float, 16> Matrix4x4::Raw() const
{
    return m_impl->Raw();
}
} // namespace FIRE