#ifndef FIRE_Renderable_h
#define FIRE_Renderable_H

#include <FIRE/Mesh.h>
#include <string>
namespace FIRE
{

class Renderable
{
public:
    explicit Renderable(std::string name);
    void SetMesh(Mesh mesh);
    Mesh& GetMesh();
    Mesh const& GetMesh() const;
    std::string GetName() const;
    std::string GetMaterial() const;

private:
    std::string m_name;
    std::string m_material{"Default"};
    Mesh m_mesh{""};
};

bool operator==(Renderable const& lhs, Renderable const& rhs);
bool operator!=(Renderable const& lhs, Renderable const& rhs);

} // namespace FIRE

#endif
