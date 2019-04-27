#ifndef FIRE_DrawAgent_h
#define FIRE_DrawAgent_h
#include <tuple>
namespace FIRE
{
class Renderable;
class DrawAgent
{
public:
    virtual ~DrawAgent() = default;

    virtual void Draw(
        Renderable const&,
        std::tuple<unsigned int, unsigned int, unsigned int> buffers) = 0;

    virtual void Clear() {}
};

} // namespace FIRE

#endif // !FIRE_DrawAgent_h
