#ifndef FIRE_TEXTUREFACTORYMOCK_H
#define FIRE_TEXTUREFACTORYMOCK_H
#include "TextureFactory.h"
#include <FIRE/Texture2D.h>
#include <cstdint>
#include <gmock/gmock.h>
namespace FIRE_tests
{
class TextureFactoryMock : public FIRE::TextureFactory
{
public:
    MOCK_METHOD6(Create2DTexture, std::unique_ptr<FIRE::Texture2D>(uint32_t, uint32_t, std::vector<uint8_t> const&, uint8_t, FIRE::Texture2D::WrappingMode, FIRE::Texture2D::Filter));
};
} // namespace FIRE_tests

#endif //FIRE_TEXTUREFACTORYMOCK_H
