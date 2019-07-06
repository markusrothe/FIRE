#ifndef SceneComponentMock_h
#define SceneComponentMock_h

#include <FIRE/SceneComponent.h>
#include <gmock/gmock.h>

namespace Mocks
{
class SceneComponentMock : public FIRE::SceneComponent
{
public:
    MOCK_METHOD1(Update, void(FIRE::Camera& cam));
    MOCK_CONST_METHOD0(CollectRenderables, std::vector<FIRE::Renderable>());
    MOCK_CONST_METHOD0(CollectTextOverlays, std::vector<FIRE::TextOverlay>());
};
} // namespace Mocks

#endif // SceneComponentMock_h
