#ifndef FIRE_glm_wrapper_h
#define FIRE_glm_wrapper_h

#define GLM_FORCE_CXX17

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#ifdef _WIN32
#pragma warning(pop)
#endif

namespace glm_helper
{
using array4x4 = std::array<float, 16>;
inline array4x4 matToArray(glm::mat4x4 const& mat)
{
    array4x4 arr;
    auto rawData = glm::value_ptr<float>(mat);
    std::copy(rawData, rawData + arr.max_size(), arr.begin());
    return arr;
}

} // namespace glm_helper

#endif // !FIRE_glm_wrapper_h
