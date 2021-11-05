
add_executable ("01_Test_01" WIN32
    "src/main.cpp"
)

target_include_directories("01_Test_01" PRIVATE ${PATTERNS_INCLUDES})

target_link_libraries("01_Test_01" PRIVATE ${PATTERNS_LIBS})
