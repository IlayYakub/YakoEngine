# Project Info
project(YakoEngineLibTester)

# Source Tree
file(GLOB_RECURSE Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	*.h
	*.hpp
	*.cpp
	*.txt
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source})

# EngineTester Target
add_executable(YakoEngineLibTester ${Source})
set_target_properties(YakoEngineLibTester PROPERTIES FOLDER "Engine")
target_include_directories(YakoEngineLibTester PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(YakoEngineLibTester PRIVATE YakoEngineLib)