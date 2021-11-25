
add_executable ("02_Command_01_Configure_Input_and_Actors"
    "src/main.cpp"
    "src/Application.cpp"
    "src/global.cpp"
    "src/InputHandler.cpp"
    "src/Dwarf.cpp"
    "src/KeybindUI.cpp"
)

target_include_directories("02_Command_01_Configure_Input_and_Actors" PRIVATE ${PATTERNS_INCLUDES})

target_link_libraries("02_Command_01_Configure_Input_and_Actors" PRIVATE ${PATTERNS_LIBS})

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo)
endif()
