#include <FIRE/RenderingComponent.h>

namespace FIRE
{
RenderingComponent::RenderingComponent(Renderer& renderer)
    : m_renderer(renderer)
{
}

RenderingComponent::~RenderingComponent() = default;

void RenderingComponent::Setup(SceneObject&)
{
    // base implementation, do nothing
}

void RenderingComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(deltaTime, sceneObject, scene);
}

} // namespace FIRE
