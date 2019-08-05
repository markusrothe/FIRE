#ifndef FIRE_GLTexture2D_h
#define FIRE_GLTexture2D_h

#include <FIRE/Texture2D.h>

namespace FIRE
{
class GLTexture2D : public Texture2D
{
public:
    GLTexture2D() = default;
    GLTexture2D(uint32_t width, uint32_t height, std::vector<uint8_t> data);

    ~GLTexture2D() override;

    uint32_t Id() const override;
    uint32_t Width() const override;
    uint32_t Height() const override;
    std::vector<uint8_t> const& Data() const override;

    void Bind(uint32_t unit) override;
    void Release() override;

private:
    uint32_t m_width;
    uint32_t m_height;
    std::vector<uint8_t> m_data;
    uint32_t m_id{};
};

} // namespace FIRE

#endif // !FIRE_GLTexture2D_h
