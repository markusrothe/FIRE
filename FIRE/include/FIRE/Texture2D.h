#ifndef FIRE_Texture_h
#define FIRE_Texture_h

#include <cstdint>
#include <memory>
#include <vector>

namespace FIRE
{
class Texture2D
{
public:
    enum class WrappingMode
    {
        WRAP,
        CLAMP,
        MIRROR
    };

    enum class Filter
    {
        NEAREST,
        LINEAR
    };

    virtual ~Texture2D() = default;

    [[nodiscard]] virtual uint32_t Id() const = 0;
    [[nodiscard]] virtual uint32_t Width() const = 0;
    [[nodiscard]] virtual uint32_t Height() const = 0;
    [[nodiscard]] virtual std::vector<uint8_t> const& Data() const = 0;

    virtual void Bind(uint32_t unit) = 0;
    virtual void Release() = 0;
};
} // namespace FIRE

#endif
