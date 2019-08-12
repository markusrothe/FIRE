#include <FIRE/AssetFacade.h>
#include <FIRE/OverlayBuilder.h>
#include <sstream>

namespace FIRE
{
OverlayBuilder::OverlayBuilder(AssetFacade& assets, std::string const& namePrefix, uint32_t count)
{
    overlays.reserve(count);

    for(auto i = 0u; i < count; ++i)
    {
        std::stringstream ss;
        ss << i;
        auto mat = assets.GetMaterial("TextDefault");
        mat.SetShaderParameter("textColor", FIRE::ShaderParameterType::VEC3, glm::vec3(1.0f, 1.0f, 1.0f));
        mat.SetShaderParameter("projection", FIRE::ShaderParameterType::MAT4x4, glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));
        overlays.emplace_back(namePrefix + ss.str(), "", 0.0f, 0.0f, mat);
    }
}

OverlayBuilder& OverlayBuilder::WithText(std::string const& text)
{
    if(textIdx >= overlays.size())
    {
        throw std::runtime_error("Could not add text. Too few overlays");
    }
    overlays[textIdx++].text = text;
    return *this;
}

std::vector<TextOverlay> OverlayBuilder::Build()
{
    return overlays;
}

OverlayBuilder& OverlayBuilder::At(float x, float y)
{
    if(atIdx >= overlays.size())
    {
        throw std::runtime_error("Could not specify position. Too few overlays");
    }
    overlays[atIdx].x = x;
    overlays[atIdx].y = y;
    atIdx++;
    return *this;
}
OverlayBuilder& OverlayBuilder::ScaledBy(float scale)
{
    if(scaleIdx >= overlays.size())
    {
        throw std::runtime_error("Could not specify scale factor. Too few overlays");
    }
    overlays[scaleIdx++].scale = scale;
    return *this;
}
} // namespace FIRE
