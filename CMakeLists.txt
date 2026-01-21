cmake_minimum_required(VERSION 3.10)
project(fpsGameEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(fpsGameEngine src/config.h src/main.cpp src/glad.c)

target_include_directories(fpsGameEngine PRIVATE dependencies shader src)

target_link_libraries(fpsGameEngine 
    glfw
    OpenGL::GL
)