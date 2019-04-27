#ifndef FIRE_Renderable_h
#define FIRE_Renderable_h

#include <FIRE/Matrix.h>
#include <FIRE/Mesh.h>
#include <string>
#include <utility>

namespace FIRE
{

class Renderable
{
public:
    explicit Renderable(std::string name);
    void SetMesh(Mesh mesh);
    Mesh& GetMesh();
    Mesh const& GetMesh() const;
    void SetName(std::string name);
    std::string Name() const;
    std::string GetMaterial() const;

    std::pair<std::string, Matrix4x4> GetShaderUniformMat4x4() const;
    void SetShaderUniformMat4x4(std::string const& uniformName, Matrix4x4 const& mat);

private:
    std::string m_name;
    std::string m_material{"Default"};
    Mesh m_mesh{""};

    std::pair<std::string, Matrix4x4>
        m_uniformVals;
};

bool operator==(Renderable const& lhs, Renderable const& rhs);
bool operator!=(Renderable const& lhs, Renderable const& rhs);

} // namespace FIRE

#endif // FIRE_Renderable_h
