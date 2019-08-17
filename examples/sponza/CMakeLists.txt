add_executable(sponza
    src/main.cpp
    )

target_include_directories(sponza
    PRIVATE
    src
    )

target_link_libraries(sponza
    PRIVATE
    FIRE
    FIRE::CompileOptions
    stb_image
    )

install(
    TARGETS sponza
    DESTINATION bin/sponza
)

install(
    FILES
    $<TARGET_PROPERTY:FIRE,RESOURCE>
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/sponza.obj
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/sponza.mtl
    DESTINATION bin/sponza
)

install(
    DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/textures
    DESTINATION bin/sponza
)

