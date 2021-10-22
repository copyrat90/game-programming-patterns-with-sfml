
cmake_minimum_required (VERSION 3.8)


add_executable ("02-Command"
    "main.cpp" 
)

target_link_libraries ("02-Command"
PRIVATE
    sfml-main
    sfml-system
    sfml-window

    ImGui-SFML::ImGui-SFML
)
