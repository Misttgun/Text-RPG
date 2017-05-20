cmake_minimum_required(VERSION 2.8)
project(Tower)

# Set target to C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Move assets folder to output folder
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Move data folder to output folder
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

# Bring the headers into the project
include_directories(include)

# Bring the sources into the project
file(GLOB SOURCES "src/*.cpp")

add_executable(tog-game ${SOURCES})