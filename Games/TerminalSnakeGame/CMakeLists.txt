# Project Info
project(TerminalSnakeGame)

# Source Tree
file(GLOB_RECURSE Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	*.h
	*.hpp
	*.cpp
	*.txt
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source})

# TerminalSnakeGame Target
add_executable(TerminalSnakeGame ${Source})
set_target_properties(TerminalSnakeGame PROPERTIES FOLDER "Games")
target_include_directories(TerminalSnakeGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(TerminalSnakeGame PRIVATE YakoEngineLib)