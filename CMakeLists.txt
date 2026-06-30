# General Info
cmake_minimum_required(VERSION 4.2.1)
project(YakoEngine)

# Common Settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_REQUIRED ON)
if(MSVC)
    add_compile_options(/Zc:preprocessor /W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin/Runtime/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin/Library/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin/Library/$<CONFIG>)

# Options
option(CXX_SANDBOX "Build YakoCxx" ON)
option(ENGINE_BUILD "Build Engine and EngineTester" ON)
option(ENGINE_BUILD_SANDBOX "Build SandBox" ON)
option(ENGINE_BUILD_GAMES "Build Games based on Engine" ON)

# Build
if(ENGINE_BUILD)
	add_subdirectory(YakoEngine)
	add_subdirectory(YakoEngineTester)
endif()

if(ENGINE_BUILD_SANDBOX)
	add_subdirectory(Sandbox)
endif()

if(ENGINE_BUILD_GAMES)
	add_subdirectory(Games)
endif()

if(CXX_SANDBOX)
	add_subdirectory(YakoCxx)
endif()