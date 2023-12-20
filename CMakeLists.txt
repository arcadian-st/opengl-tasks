cmake_minimum_required(VERSION 3.17)

project(opengl_tasks)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES src/main.cpp src/glad.c)
add_executable(main ${SOURCE_FILES})

include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(main glfw3)