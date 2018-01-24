#include "renderableManager.h"
#include "material.h"

#include <algorithm>
#include <utility>
#include <iostream>

namespace blocks
{
    RenderableManager::RenderableToken RenderableManager::AddRenderable(Renderable const& renderable)
    {
        auto const insertionResult = m_renderables.insert(std::make_pair(renderable.GetName(), renderable));

        if (!insertionResult.second)
        {
            std::cout << "RenderableManager::AddRenderable. Element with name=" << renderable.GetName() << " already present\n";
        }

        return insertionResult.first;
    }

    void RenderableManager::RenderRenderables()
    {
        for (auto& renderable : m_renderables)
        {
            renderable.second.Render();
        }
    }

}
