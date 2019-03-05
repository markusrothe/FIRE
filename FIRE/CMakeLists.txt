add_library(FIRE STATIC
	include/FIRE/FIRE.h
	src/FIRE.cpp
)

target_include_directories(FIRE
PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
  $<INSTALL_INTERFACE:include> 
)

add_subdirectory(test)