#ifndef fire_shaderlinker_h
#define fire_shaderlinker_h

namespace Fire
{
class ShaderLinker
{
public:
    virtual ~ShaderLinker() = default;

    virtual int Link() = 0;
};
} // namespace Fire

#endif // fire_shaderlinker_h