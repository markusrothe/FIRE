#ifndef FIRE_Uploader_h
#define FIRE_Uploader_h
#include <tuple>
namespace FIRE
{
class Renderable;
class Uploader
{
public:
    virtual ~Uploader() = default;

    virtual std::tuple<unsigned int, unsigned int, unsigned int>
    Upload(Renderable const& renderable) = 0;
};
} // namespace FIRE

#endif
