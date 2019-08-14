//#include "FPSOverlayComponent.h"
//#include <FIRE/AssetFacade.h>
//#include <FIRE/Message.h>
//#include <FIRE/Renderer.h>
//#include <FIRE/TextOverlay.h>
//#include <sstream>
//namespace examples
//{
//
//FPSOverlayComponent::FPSOverlayComponent(FIRE::Renderer& renderer, FIRE::AssetFacade& assets)
//    : FIRE::RenderingComponent(renderer, {})
//    , assets(assets)
//{
//}
//
//void FPSOverlayComponent::DoUpdate(double deltaTime, FIRE::SceneObject&, FIRE::Scene&)
//{
//    std::stringstream ss;
//    ss << static_cast<int>(1.0 / deltaTime);
//
//    auto overlays = assets.CreateTextOverlays("fps-counter", 1u)
//                        .At(0.01f, 0.01f)
//                        .ScaledBy(0.5f)
//                        .WithText(ss.str())
//                        .Build();
//
//    for(auto const& overlay : overlays)
//    {
//        m_renderer.Submit(overlay);
//    }
//}
//
//std::optional<std::any> FPSOverlayComponent::Receive(FIRE::Message, FIRE::SceneObject&)
//{
//    return std::nullopt;
//}
//} // namespace examples
