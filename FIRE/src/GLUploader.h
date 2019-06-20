#ifndef FIRE_GLUploader_h
#define FIRE_GLUploader_h

#include "Uploader.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <memory>
#include <unordered_map>
namespace FIRE
{
class Renderable;

class GLUploader : public Uploader
{
public:
    ~GLUploader() override = default;

    std::tuple<GLuint, GLuint, GLuint> Upload(Renderable const& renderable) override;

private:
    std::unordered_map<std::string, std::tuple<GLuint, GLuint, GLuint>> m_uploadedRenderables;
};
} // namespace FIRE

#endif // !FIRE_GLUploader_h
