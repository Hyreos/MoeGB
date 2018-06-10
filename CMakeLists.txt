cmake_minimum_required(VERSION 3.3)

project(MoeGB)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_compile_options("-fpermissive")

file(GLOB FSRC
    "*.cpp"
)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(moegb ${FSRC})
target_link_libraries(moegb sfml-window sfml-graphics sfml-system)