cmake_minimum_required(VERSION 3.20)

project(liminal-ambiente)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include raylib subproject so its `raylib` target is available
add_subdirectory(external/raylib)

add_executable(liminal-ambiente
	src/main.cpp
	src/rain.cpp
	src/tree.cpp
	src/fog.cpp
)

# Ensure our `src` headers are visible to the target
target_include_directories(liminal-ambiente PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link the raylib target to the executable
target_link_libraries(liminal-ambiente PRIVATE raylib)