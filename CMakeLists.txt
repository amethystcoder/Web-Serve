cmake_minimum_required(VERSION 3.16)
project(Celeris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp  
    src/*.h
    src/*.hpp 
)
 
add_executable(Celeris ${SOURCES})
target_include_directories(Celeris PUBLIC src)

# Only link stdc++fs on non-MSVC compilers (e.g., GCC/Clang)
if(NOT MSVC)
    target_link_libraries(Celeris PRIVATE stdc++fs)
endif()