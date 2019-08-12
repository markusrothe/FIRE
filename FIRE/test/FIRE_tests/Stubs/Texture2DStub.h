#ifndef FIRE_TEXTURE2DSTUB_H
#define FIRE_TEXTURE2DSTUB_H
#include <FIRE/Texture2D.h>
namespace FIRE_tests
{
class Texture2DStub : public FIRE::Texture2D
{
public:
    explicit Texture2DStub(uint32_t id)
        : m_id(id)
    {
    }

    [[nodiscard]] uint32_t Id() const override
    {
        return m_id;
    }

    [[nodiscard]] uint32_t Width() const override
    {
        return 100u;
    }

    [[nodiscard]] uint32_t Height() const override
    {
        return 200u;
    }

    [[nodiscard]] std::vector<uint8_t> const& Data() const override
    {
        return m_data;
    }

    void Bind(uint32_t /*unit*/) override
    {
    }

    void Release() override
    {
    }

private:
    uint32_t m_id;
    std::vector<uint8_t> m_data{0x00, 0xff, 0xff, 0x00};
};
} // namespace FIRE_tests
#endif //FIRE_TEXTURE2DSTUB_H
