# Project Info
project(YakoEngine)

# Source Tree
file(GLOB_RECURSE Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	*.h
	*.hpp
	*.cpp
	*.txt
	*.cmake
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source})

# Engine Target
add_library(YakoEngineLib STATIC ${Source})
set_target_properties(YakoEngineLib PROPERTIES FOLDER "Engine")
target_include_directories(YakoEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_precompile_headers(YakoEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/pch.h)

include(YakoEngineDependencies.cmake)