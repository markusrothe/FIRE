# add a new library target with its source files
add_library(FIRE STATIC
	include/FIRE/FIRE.h
	src/FIRE.cpp
)

# Add include directories to the target 
target_include_directories(FIRE
PUBLIC # Populate the INTERFACE_INCLUDE_DIRECTORIES property to expose the public headers of this target

  # used by other targets in this project 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 

  # relative path used in conjunction with the CMAKE_INSTALL_PREFIX (for exporting using install(EXPORT))
  $<INSTALL_INTERFACE:include> 
)
