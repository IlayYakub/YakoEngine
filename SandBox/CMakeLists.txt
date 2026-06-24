# Project Info
project(SandBox)

# Source Tree
file(GLOB_RECURSE Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	*.h
	*.hpp
	*.cpp
	*.txt
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source})

# SandBox Target
add_executable(SandBox ${Source})
set_target_properties(SandBox PROPERTIES FOLDER "SandBox")
target_include_directories(SandBox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(SandBox PRIVATE YakoEngineLib)