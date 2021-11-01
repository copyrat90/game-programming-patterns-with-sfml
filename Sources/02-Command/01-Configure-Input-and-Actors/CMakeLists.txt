
add_executable ("02_Command_01_Configure_Input_and_Actors"
    "main.cpp" 
)

target_link_libraries ("02_Command_01_Configure_Input_and_Actors"
PRIVATE
    sfml-main
    sfml-system
    sfml-window

    ImGui-SFML::ImGui-SFML
)
