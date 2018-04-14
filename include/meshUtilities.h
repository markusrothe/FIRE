#ifndef blocks_meshUtilities_h
#define blocks_meshUtilities_h

#include <vector>

namespace blocks
{
    class Mesh;
    
    enum class Dimension
    {
        TWO_D,
        THREE_D      
    };
    
    std::vector<float> SerializeMeshData(Mesh const& mesh, Dimension vertexDimension, Dimension texCoordDimension);
}

#endif // blocks_meshUtilities_h
