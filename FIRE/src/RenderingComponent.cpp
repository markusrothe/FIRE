#include <FIRE/RenderingComponent.h>

namespace FIRE
{
RenderingComponent::RenderingComponent(Renderer& renderer)
    : m_renderer(renderer)
{
}

RenderingComponent::~RenderingComponent() = default;

void RenderingComponent::Update(SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(sceneObject, scene);
}

} // namespace FIRE
