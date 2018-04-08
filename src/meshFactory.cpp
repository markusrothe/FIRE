#include "meshFactory.h"
#include "texture.h"
#include <vector>
#include <glm/glm.hpp>
#include <utility>

namespace blocks
{
    namespace MeshFactory
    {        
        Mesh CreateQuad(unsigned int xMax, unsigned int zMax, unsigned int texCoordMax)
        {
            std::vector<glm::vec3> vertices = {        
                glm::vec3(0, 0, 0), 
                glm::vec3(xMax, 0, 0),
                glm::vec3(0, 0, zMax),
                glm::vec3(xMax, 0, zMax)};

            std::vector<glm::vec2> texCoords = {
                glm::vec2(0, 0),
                glm::vec2(texCoordMax, 0),
                glm::vec2(0, texCoordMax),
                glm::vec2(texCoordMax, texCoordMax) };
        
            std::vector<glm::vec3> normals(4, glm::vec3(0, 1, 0));

            std::vector<unsigned int> indices = {0, 1, 2, 2, 1, 3};
        
            return Mesh(std::move(vertices), std::move(normals), std::move(texCoords), std::move(indices));
        }

        Mesh CreateCharBillboard(unsigned int screenX, unsigned int screenY, CharTexture const * const tex)
        {
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<unsigned int> indices;
            std::vector<glm::vec2> texCoords;

            // Cast to int to avoid unsigned overflows and the
            // billboards to cover half the screen due to that overflow.
            // This is especially true if screenY == 0. The baseline of the char glyph
            // would move below the screen and come out back on top of the screen
            auto const x = static_cast<int>(tex->GetBearing().x + screenX);
            auto const y = static_cast<int>(screenY - (tex->GetSize().y - tex->GetBearing().y));

            auto const w = tex->GetSize().x;
            auto const h = tex->GetSize().y;

            vertices.push_back({ x, y + h, 0 });
            texCoords.push_back({ 0.0, 0.0 });

            vertices.push_back({ x, y, 0 });
            texCoords.push_back({ 0.0, 1.0 });

            vertices.push_back({ x + w, y, 0 });
            texCoords.push_back({ 1.0, 1.0 });

            vertices.push_back({ x + w, y + h, 0 });
            texCoords.push_back({ 1.0, 0.0 });

            indices.push_back(0);
            indices.push_back(1);
            indices.push_back(2);

            indices.push_back(0);
            indices.push_back(2);
            indices.push_back(3);

            return Mesh(std::move(vertices), std::move(normals), std::move(texCoords), std::move(indices));
        }                
    } // namespace MeshFactory
} // namespace blocks
