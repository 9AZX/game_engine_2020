cmake_minimum_required(VERSION 3.12.0)

set(
    CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

set(
   CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS
   ON
)

project(3DGE
    VERSION 0.1
    DESCRIPTION "3D Game Engine EPITECH project"
    LANGUAGES CXX
)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CompileOptionsUtils.cmake)

add_subdirectory(source)
add_subdirectory(app)
