#ifndef material_h
#define material_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <functional>
#include <string>
#include <vector>

namespace blocks
{
    class Material
    {
    public:
        Material(std::string const name, std::vector<std::string> const& locations, GLuint shaderProgram);

        std::vector<std::string> const& GetLocations() const;

        GLuint GetShaderID() const;

        void Bind() const;
        void Unbind() const;

        void Uniform(glm::mat4x4 const& matrix, std::string const name) const;
        void Uniform(unsigned int i, std::string const name) const;

    private:
        std::string const m_name;
        std::vector<std::string> m_locations;
        GLuint m_shaderID;
    };
}

#endif // material_h
