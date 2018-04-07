#include "meshUtilities.h"
#include "mesh.h"

namespace blocks
{       
    std::vector<float> SerializeMeshData(Mesh const& mesh, Dimension vertexDimension
                                         , Dimension texCoordDimension)
    {
        std::vector<float> data;

        for (auto const& vertex : mesh.GetVertices())
        {
            if (Dimension::TWO_D == vertexDimension)
            {
                data.push_back(vertex.x);
                data.push_back(vertex.y);
            }

            if (Dimension::THREE_D == vertexDimension)
            {
                data.push_back(vertex.x);
                data.push_back(vertex.y);
                data.push_back(vertex.z);
            }            
        }

        for (auto const& texCoord : mesh.GetTexCoords())
        {
            if (Dimension::TWO_D == texCoordDimension)
            {
                data.push_back(texCoord.x);
                data.push_back(texCoord.y);
            }
        }

        return data;
    }
    
} // namespace blocks
