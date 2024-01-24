# CMakeLists.txt
# cmake -S .. -B ../build -G "MinGW Makefiles"
cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

project(CraftMine VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(headers INTERFACE)

target_include_directories(headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)