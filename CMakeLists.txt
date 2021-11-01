
cmake_minimum_required (VERSION 3.8)
project ("interactive-game-programming-patterns")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED true)

find_package (SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package (ImGui CONFIG REQUIRED)
find_package (ImGui-SFML CONFIG REQUIRED)

add_subdirectory ("02-Command")
