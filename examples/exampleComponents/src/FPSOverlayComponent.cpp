#include "FPSOverlayComponent.h"
#include <FIRE/MaterialFactory.h>
#include <FIRE/Message.h>
#include <FIRE/Renderer.h>
#include <FIRE/TextOverlay.h>
#include <sstream>
namespace examples
{

FPSOverlayComponent::FPSOverlayComponent(FIRE::Renderer& renderer, FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
    , m_material(materialFactory.GetMaterial("text"))
{
}

void FPSOverlayComponent::DoUpdate(double deltaTime, FIRE::SceneObject&, FIRE::Scene&)
{
    m_material.SetShaderParameter("textColor", FIRE::ShaderParameterType::VEC3, glm::vec3(1.0f, 1.0f, 1.0f));
    m_material.SetShaderParameter("projection", FIRE::ShaderParameterType::MAT4x4, glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));

    std::stringstream ss;
    ss << static_cast<int>(1.0 / deltaTime);

    m_renderer.Submit(FIRE::TextOverlay("fpsOverlay", ss.str(), 0.02f, 0.02f, m_material, 0.5f));
}

std::optional<std::any> FPSOverlayComponent::Receive(FIRE::Message, FIRE::SceneObject&)
{
    return std::nullopt;
}
} // namespace examples
