#ifndef blocks_renderableManager_h
#define blocks_renderableManager_h

#include "renderable.h"
#include <map>
#include <string>

namespace blocks
{
    class RenderableManager
    {
    public:
        typedef std::map<std::string, Renderable> RenderableMap;
        typedef RenderableMap::const_iterator RenderableToken;

        RenderableToken AddRenderable(Renderable const& renderable);

        void RenderRenderables();

    private:
        RenderableMap m_renderables;
    };
}

#endif // blocks_renderableManager_h
