cmake_minimum_required(VERSION 3.8)
project(parkman)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_compile_options(parkman PUBLIC "-Wall")
target_include_directories(parkman PUBLIC ${SDL2_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(parkman PUBLIC ${SDL2_LIBRARIES})
