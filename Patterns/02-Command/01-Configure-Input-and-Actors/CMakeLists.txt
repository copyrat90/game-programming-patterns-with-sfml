
add_executable ("02_Command_01_Configure_Input_and_Actors" WIN32
    "main.cpp"
)

target_include_directories("02_Command_01_Configure_Input_and_Actors" PRIVATE ${PATTERNS_INCLUDES})

target_link_libraries("02_Command_01_Configure_Input_and_Actors" PRIVATE ${PATTERNS_LIBS})
