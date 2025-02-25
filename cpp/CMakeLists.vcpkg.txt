cmake_minimum_required(VERSION 3.16)

project(example VERSION 1.0 LANGUAGES CXX)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(filerix CONFIG REQUIRED)

set(SOURCES
  src/example.cc
)

add_executable(example ${SOURCES})
target_link_libraries(example PRIVATE filerix::filerix)
