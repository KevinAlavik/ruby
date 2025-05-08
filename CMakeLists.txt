cmake_minimum_required(VERSION 3.15)
project(ProjectRuby VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
if(NOT COMPILER_SUPPORTS_CXX17)
    message(FATAL_ERROR "The compiler does not support C++17.")
endif()

if(NOT (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64"))
    message(FATAL_ERROR "This project only supports Linux on x86_64 architecture.")
endif()

set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/External/raylib-5.5_linux_amd64)
set(RAYLIB_INCLUDE_DIR ${RAYLIB_DIR}/include)
set(RAYLIB_LIBRARY_DIR ${RAYLIB_DIR}/lib)

set(RAYLIB_CPP_DIR ${CMAKE_SOURCE_DIR}/External/raylib-cpp-5.5.0/include)

if(NOT EXISTS ${RAYLIB_INCLUDE_DIR}/raylib.h)
    message(FATAL_ERROR "raylib.h not found in ${RAYLIB_INCLUDE_DIR}")
endif()
if(NOT EXISTS ${RAYLIB_LIBRARY_DIR}/libraylib.so AND NOT EXISTS ${RAYLIB_LIBRARY_DIR}/libraylib.a)
    message(FATAL_ERROR "Raylib library (.so or .a) not found in ${RAYLIB_LIBRARY_DIR}")
endif()

include_directories(${RAYLIB_INCLUDE_DIR})
include_directories(${RAYLIB_CPP_DIR})

link_directories(${RAYLIB_LIBRARY_DIR})

set(SPDLOG_DIR ${CMAKE_SOURCE_DIR}/External/spdlog-1.15.2)
include_directories(${SPDLOG_DIR}/include)
add_subdirectory(${SPDLOG_DIR})

set(SOURCE_DIRS
    .
    Core
    Utils
    Render
)

set(SOURCES)
foreach(DIR ${SOURCE_DIRS})
    file(GLOB DIR_SOURCES "${DIR}/*.cpp" "${DIR}/*.hpp")
    list(APPEND SOURCES ${DIR_SOURCES})
endforeach()

INCLUDE_DIRECTORIES(${SOURCE_DIRS})

add_executable(ruby ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring Debug build with AddressSanitizer")
    target_compile_options(ruby PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
        -O0
        -g3
    )
    target_link_options(ruby PRIVATE
        -fsanitize=address
    )
endif()

target_link_libraries(ruby PRIVATE raylib m dl pthread spdlog)
target_include_directories(ruby PRIVATE ${SOURCE_DIRS})
