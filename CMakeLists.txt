cmake_minimum_required(VERSION 3.16)
project(Celeris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Collect all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp  
    src/*.h
    src/*.hpp
)

# add_subdirectory(src) 

# Executable
add_executable(Celeris ${SOURCES})

# Include directories (if using headers outside src/)
target_include_directories(Celeris PUBLIC src)