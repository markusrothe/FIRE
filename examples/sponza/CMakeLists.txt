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
    FIRE::exampleComponents
)

install(
    TARGETS sponza
    DESTINATION bin/sponza
)

file(GLOB_RECURSE assets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
install(
    FILES 
    $<TARGET_PROPERTY:FIRE,RESOURCE>
    ${assets}
    DESTINATION bin/sponza
)

