if(NOT BUILD_TESTING)
    return()
endif()

add_executable(FIRE_tests
    ./FIRETest.cpp
)

target_link_libraries(FIRE_tests
PRIVATE
    FIRE
    gtest
    gtest_main
    gmock
)

if(MSVC)
    target_compile_options(FIRE_tests PRIVATE /W4 /WX)
else()
    target_compile_options(FIRE_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND COVERAGE)
    target_compile_options(FIRE_tests PUBLIC --coverage)
    target_link_libraries(FIRE_tests PUBLIC --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(FIRE_tests)

add_custom_command(
    TARGET FIRE_tests POST_BUILD
    COMMAND ctest -C $<CONFIGURATION> --output-on-failure
)
