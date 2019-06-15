#ifndef FIRE_Material_h
#define FIRE_Material_h
#include <string>
namespace FIRE
{
class Material
{
public:
    Material() = default;
    Material(std::string name, unsigned int shaderId);

    std::string Name() const;
    unsigned int ShaderId() const;

private:
    std::string m_name{""};
    unsigned int m_shaderId{0};
};
} // namespace FIRE

#endif