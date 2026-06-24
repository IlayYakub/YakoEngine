# google test
find_package(GTest REQUIRED)
target_link_libraries(YakoEngineLib PRIVATE gtest::gtest)

# spdlog
find_package(spdlog REQUIRED)
target_link_libraries(YakoEngineLib PRIVATE spdlog::spdlog)

# glfw
find_package(glfw3 REQUIRED)
target_link_libraries(YakoEngineLib PRIVATE glfw)