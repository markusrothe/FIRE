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

include(GoogleTest)
gtest_discover_tests(FIRE_tests)

add_custom_command(TARGET FIRE_tests POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure
)