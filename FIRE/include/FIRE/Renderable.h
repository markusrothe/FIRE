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

    void SetMesh(std::shared_ptr<Mesh> const& mesh);
    Mesh& GetMesh();
    Mesh const& GetMesh() const;

    void SetName(std::string name);
    std::string Name() const;

    void SetMaterial(Material material);
    Material const& GetMaterial() const;
    Material& GetMaterial();

    Transform& GetTransform();

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

bool operator==(Renderable const& lhs, Renderable const& rhs);
bool operator!=(Renderable const& lhs, Renderable const& rhs);

} // namespace FIRE

#endif // FIRE_Renderable_h
