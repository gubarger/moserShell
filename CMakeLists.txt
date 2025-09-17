cmake_minimum_required(VERSION 3.10)
project(moser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "include/*.cpp"
    "source/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

find_package(PkgConfig REQUIRED)
pkg_search_module(READLINE REQUIRED readline)

target_include_directories(${PROJECT_NAME} PRIVATE ${READLINE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${READLINE_LIBRARIES})