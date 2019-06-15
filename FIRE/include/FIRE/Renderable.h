#ifndef FIRE_Renderable_h
#define FIRE_Renderable_h

#include <FIRE/Material.h>
#include <FIRE/Matrix.h>
#include <FIRE/Mesh.h>
#include <FIRE/Transform.h>
#include <FIRE/Vector.h>
#include <memory>
#include <string>
#include <utility>

namespace FIRE
{

class Renderable
{
public:
    explicit Renderable(std::string name);
    ~Renderable();
    void SetMesh(Mesh mesh);
    Mesh& GetMesh();
    Mesh const& GetMesh() const;
    void SetName(std::string name);
    std::string Name() const;
    void SetMaterial(Material material);
    Material GetMaterial() const;
    Transform& GetTransform();

    std::pair<std::string, Matrix4x4> GetShaderUniformMat4x4() const;
    void SetShaderUniformMat4x4(std::string const& uniformName, Matrix4x4 const& mat);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

bool operator==(Renderable const& lhs, Renderable const& rhs);
bool operator!=(Renderable const& lhs, Renderable const& rhs);

} // namespace FIRE

#endif // FIRE_Renderable_h
