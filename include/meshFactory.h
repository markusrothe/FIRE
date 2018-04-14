#ifndef blocks_meshFactory_h
#define blocks_meshFactory_h

#include "mesh.h"

namespace blocks
{
    class CharTexture;
    
    namespace MeshFactory
    {                
        Mesh CreateQuad(unsigned int xMax, unsigned int zMax, unsigned int texCoordMax);
        Mesh CreateCharBillboard(unsigned int screenX, unsigned int screenY, CharTexture const * const tex);
    } // namespace MeshFactory
} // namespace blocks

#endif // blocks_meshFactory_h
