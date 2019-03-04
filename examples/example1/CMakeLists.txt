# add a new executable with its sources
add_executable(example1
	main.cpp
)

# specify the libraries that our executable will link in
target_link_libraries(example1
PRIVATE
	FIRE
)