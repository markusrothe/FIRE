#ifndef fire_glslshaderlinker_h
#define fire_glslshaderlinker_h

#include "shaderLinker.h"

namespace Fire
{
class GLSLShaderLinker : public ShaderLinker
{
public:
    GLSLShaderLinker();
    int Link() override;
};
} // namespace Fire

#endif // fire_glslshaderlinker_h