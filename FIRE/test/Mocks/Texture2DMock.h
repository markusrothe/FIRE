#ifndef FIRE_TEXTURE2DMOCK_H
#define FIRE_TEXTURE2DMOCK_H
#include <FIRE/Texture2D.h>
#include <gmock/gmock.h>

namespace FIRE_tests
{
class Texture2DMock : public FIRE::Texture2D
{
public:
    MOCK_CONST_METHOD0(Id, uint32_t(void));
    MOCK_CONST_METHOD0(Width, uint32_t(void));
    MOCK_CONST_METHOD0(Height, uint32_t(void));
    MOCK_CONST_METHOD0(Data, std::vector<uint8_t> const&(void));
    MOCK_METHOD1(Bind, void(uint32_t));
    MOCK_METHOD0(Release, void());
};
} // namespace FIRE_tests

#endif //FIRE_TEXTURE2DMOCK_H
