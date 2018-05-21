#include "textureBinder.h"
#include "renderable.h"
#include "texture.h"

namespace Fire
{
    void TextureBinder::Bind(Renderable* renderable) const
    {
        if (!renderable)
        {
            return;
        }

        auto tex = renderable->GetTexture();
        if (tex)
        {
            tex->Bind();
        }
    }

    void TextureBinder::Unbind(Renderable* renderable) const
    {
        if (!renderable)
        {
            return;
        }

        auto tex = renderable->GetTexture();
        if (tex && tex->Bound())
        {
            tex->Unbind();
        }
    }
} // namespace Fire
