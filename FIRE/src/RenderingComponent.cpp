#include <FIRE/Renderer.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{
RenderingComponent::RenderingComponent(RenderableSubmitter& submitter, std::vector<Renderable> renderables)
    : m_renderableSubmitter(submitter)
    , m_renderables(std::move(renderables))
{
}

RenderingComponent::~RenderingComponent() = default;

void RenderingComponent::Setup(SceneObject&)
{
    // base implementation, do nothing
}

void RenderingComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    auto const transform = sceneObject.GetTransform();
    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(Message(MessageID::GetViewMatrix)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(Message(MessageID::GetProjectionMatrix)).value());
    auto lightPos = std::any_cast<glm::vec3>(scene.Send(Message(MessageID::GetLightPosition)).value());
    for(auto renderable : m_renderables)
    {
        renderable.material.SetShaderParameter("M", ShaderParameterType::MAT4x4, transform.ModelMatrix());
        renderable.material.SetShaderParameter("VP", ShaderParameterType::MAT4x4, projMatrix * viewMatrix);
        renderable.material.SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);
        m_renderableSubmitter.Submit(renderable);
    }

    DoUpdate(deltaTime, sceneObject, scene);
}

void RenderingComponent::DoUpdate(double, SceneObject&, Scene&)
{
    // base implementation, do nothing
}

std::optional<std::any> RenderingComponent::Receive(Message /*msg*/, SceneObject& /*sceneObject*/)
{
    return std::nullopt;
}

} // namespace FIRE
