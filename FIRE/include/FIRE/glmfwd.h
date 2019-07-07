#ifndef FIRE_glmfwd_h
#define FIRE_glmfwd_h

#define GLM_FORCE_CXX17

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

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

#endif // !FIRE_glmfwd_h
