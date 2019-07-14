#include <FIRE/Noise.h>
#include <FastNoise/FastNoise.h>

namespace FIRE
{
namespace Noise
{

std::vector<std::vector<float>> CreateHeightmap(unsigned int x, unsigned int y)
{
    std::vector<std::vector<float>> vec;
    vec.resize(x);
    for(auto& v : vec)
    {
        v.resize(y);
    }

    FastNoise noise;
    noise.SetNoiseType(FastNoise::Cellular);
    noise.SetFrequency(0.02f);
    noise.SetCellularReturnType(FastNoise::Distance2Add);

    for(auto i = 0u; i < x; ++i)
    {
        for(auto j = 0u; j < y; ++j)
        {
            vec[i][j] = noise.GetNoise(static_cast<float>(i), static_cast<float>(j));
        }
    }

    return vec;
}

float GetNoiseValue(float x, float y)
{
    FastNoise noise;
    noise.SetNoiseType(FastNoise::Simplex);
    return noise.GetNoise(x, y);
}
} // namespace Noise

} // namespace FIRE
