# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project( editor )

# flags

# files
file(GLOB source
    "./src/main.cpp",
    "./src/editor/*.cpp"
    "./src/util/*.cpp"
    "./src/glad/glad.c"
    "./src/stb/*.cpp"
)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# include
include_directories(includes/editor)
include_directories(includes/util)
include_directories(includes/glad)
include_directories(includes/stb)
include_directories(includes/config)
find_package(glfw3 REQUIRED)

# target
add_executable( binary ${source})
target_link_libraries(binary glfw)