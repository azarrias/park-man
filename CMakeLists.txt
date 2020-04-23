cmake_minimum_required(VERSION 3.8)
project(parkman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(${CMAKE_PROJECT_NAME} "")
include("${CMAKE_SOURCE_DIR}/cmake/sourcelist.cmake")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_compile_options(parkman PUBLIC "-Wall")
target_include_directories(parkman PUBLIC ${SDL2_INCLUDE_DIRS} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(parkman PUBLIC ${SDL2_LIBRARIES} PUBLIC ${SDL2_IMAGE_LIBRARIES} PUBLIC ${SDL2_TTF_LIBRARIES})
