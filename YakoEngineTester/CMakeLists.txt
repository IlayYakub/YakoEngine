# Project Info
project(YakoEngineTester)

# Source Tree
file(GLOB_RECURSE Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	*.h
	*.hpp
	*.cpp
	*.txt
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source})

# EngineTester Target
add_executable(YakoEngineTester ${Source})
set_target_properties(YakoEngineTester PROPERTIES FOLDER "Engine")
target_include_directories(YakoEngineTester PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(YakoEngineTester PRIVATE YakoEngineLib)