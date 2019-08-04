#ifndef FIRE_TEXTUREFACTORYMOCK_H
#define FIRE_TEXTUREFACTORYMOCK_H
#include "TextureFactory.h"
#include <gmock/gmock.h>
namespace FIRE_tests
{
class TextureFactoryMock : public FIRE::TextureFactory
{
public:
    MOCK_METHOD3(Create2DTexture, std::unique_ptr<FIRE::Texture2D>(uint32_t width, uint32_t height, std::vector<uint8_t> const& data));
};
} // namespace FIRE_tests

#endif //FIRE_TEXTUREFACTORYMOCK_H
