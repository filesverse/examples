cmake_minimum_required(VERSION 3.10)

project(example VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FILERIX REQUIRED filerix)

set(SOURCES
  src/example.c
)

add_executable(example ${SOURCES})
target_link_libraries(example PRIVATE ${FILERIX_LIBRARIES})

target_include_directories(example PRIVATE ${FILERIX_INCLUDE_DIRS})
target_link_directories(example PRIVATE ${FILERIX_LIBRARY_DIRS})
