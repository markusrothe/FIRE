
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(gtest-1.8.1 EXCLUDE_FROM_ALL)
add_subdirectory(glfw-3.3 EXCLUDE_FROM_ALL)
add_subdirectory(glad EXCLUDE_FROM_ALL)
add_subdirectory(glm-0.9.9 EXCLUDE_FROM_ALL)
add_subdirectory(freetype-2.9 EXCLUDE_FROM_ALL)
add_subdirectory(FastNoise EXCLUDE_FROM_ALL)
add_subdirectory(assimp-5.0.0/assimp EXCLUDE_FROM_ALL)
add_subdirectory(stb_image EXCLUDE_FROM_ALL)