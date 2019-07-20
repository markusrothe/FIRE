#ifndef FIRE_Noise_h
#define FIRE_Noise_h
#include <vector>
namespace FIRE
{
namespace Noise
{
std::vector<std::vector<float>> CreateHeightmap(unsigned int x, unsigned int y);
float GetNoiseValue(float x, float y);
} // namespace Noise
} // namespace FIRE

#endif // FIRE_Noise_h