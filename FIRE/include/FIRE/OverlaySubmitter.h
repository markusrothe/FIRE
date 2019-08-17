#ifndef FIRE_OVERLAYSUBMITTER_H
#define FIRE_OVERLAYSUBMITTER_H

#include <FIRE/TextOverlay.h>
namespace FIRE
{
class OverlaySubmitter
{
public:
    virtual ~OverlaySubmitter() = default;
    virtual void Submit(TextOverlay const& overlay) = 0;
};
} // namespace FIRE

#endif //FIRE_OVERLAYSUBMITTER_H
