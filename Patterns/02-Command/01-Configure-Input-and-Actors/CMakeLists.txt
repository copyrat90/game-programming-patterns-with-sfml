
add_executable ("02_Command_01_Configure_Input_and_Actors" WIN32
    "main.cpp"
)

target_link_libraries ("02_Command_01_Configure_Input_and_Actors"
PRIVATE
    sfml-system
    sfml-window

    ImGui-SFML::ImGui-SFML
)

if(WIN32)
    target_link_libraries ("02_Command_01_Configure_Input_and_Actors"
    PRIVATE
        sfml-main
    )
endif()
