
set(PATTERNS_INCLUDES "${CMAKE_SOURCE_DIR}")

if(WIN32)
    set(PATTERNS_LIBS
        sfml-system
        sfml-window
        ImGui-SFML::ImGui-SFML
        sfml-main
    )
else()
    set(PATTERNS_LIBS
        sfml-system
        sfml-window
        ImGui-SFML::ImGui-SFML
    )
endif()

add_subdirectory("02-Command/01-Configure-Input-and-Actors")
