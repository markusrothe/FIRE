#ifndef blocks_assets_h
#define blocks_assets_h

#include "mesh.h"
#include "material.h"
#include "texture.h"

namespace blocks
{   
    struct Assets
    {
        Mesh m_mesh;
        Material const* m_material;
        Texture m_texture;
    };   
}

#endif // blocks_assets_h
