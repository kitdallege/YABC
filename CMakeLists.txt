cmake_minimum_required(VERSION 3.0)
project(YABC)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(include)

#include_directories("/home/kit/Installers/sdl_lib/SDL/include")
include_directories("/home/kit/Installers/sdl_lib/SDL2_image-2.0.1")

file(GLOB SOURCES "src/*.cpp")

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x")
SET(GCC_COVERAGE_LINK_FLAGS   "-lSDL2_image") # "-L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2_image")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_executable(YABC ${SOURCES})

target_link_libraries(YABC "${SDL2_LIBRARIES} -lSDL2_image")
