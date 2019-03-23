#ifndef FIRE_MaterialManager_h
#define FIRE_MaterialManager_h
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
namespace FIRE
{
class MaterialManager
{
public:
    MaterialManager();

    GLuint GetShader(std::string const& materialName) const;

private:
    std::unordered_map<std::string, GLuint> m_shaders;
};
} // namespace FIRE

#endif // !FIRE_MaterialManager_h
