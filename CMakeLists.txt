cmake_minimum_required(VERSION 2.8)

project(sempr_example_extension)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_definitions(-Wall -Wno-unknown-pragmas)

include_directories(include)

find_package(PkgConfig REQUIRED)

# find & use sempr
pkg_check_modules(SEMPR REQUIRED sempr-core)
include_directories(${SEMPR_INCLUDE_DIRS})
link_directories(${SEMPR_LIBRARY_DIRS})
add_definitions(${SEMPR_CFLAGS_OTHER})  # for the database-flag (sqlite, postgresql, ...)

# message("${SEMPR_INCLUDE_DIRS}")
# message("${SEMPR_LIBRARY_DIRS}")
# message("${SEMPR_CFLAGS_OTHER}")

add_executable(example src/example.cpp)
target_link_libraries(example ${SEMPR_LIBRARIES})
