#include "PointLightComponent.h"
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <chrono>
namespace examples
{

void PointLightComponent::Setup(FIRE::SceneObject& sceneObject)
{
    sceneObject.GetTransform().SetPosition({0.0f, 300.0f, 0.0f});
}

void PointLightComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
    auto pos = sceneObject.GetTransform().Position();
    pos.x = sinf(0.001f * static_cast<float>(time)) * 800.0f;
    sceneObject.GetTransform().SetPosition(pos);
}

std::optional<std::any> PointLightComponent::Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject)
{
    if(msg.id == FIRE::MessageID::GetLightPosition)
    {
        return sceneObject.GetTransform().Position();
    }

    return std::nullopt;
}

} // namespace examples
