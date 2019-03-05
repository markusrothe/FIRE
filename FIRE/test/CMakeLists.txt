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

add_test(
	NAME FIRETests
	COMMAND FIRE_tests
)