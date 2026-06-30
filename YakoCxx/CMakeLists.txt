# Project Info
project(YakoCxx)

# Source Tree
file(GLOB_RECURSE Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	*.h
	*.hpp
	*.cpp
	*.txt
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source})

# YakoCxx Target
add_executable(YakoCxx ${Source})
set_target_properties(YakoCxx PROPERTIES FOLDER "CXX_SANDBOX")
target_include_directories(YakoCxx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(YakoCxx PRIVATE YakoEngineLib)