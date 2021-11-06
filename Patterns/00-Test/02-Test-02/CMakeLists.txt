
add_executable ("02_Test_02" WIN32
    "src/main.cpp"
)

target_include_directories("02_Test_02" PRIVATE ${PATTERNS_INCLUDES})

target_link_libraries("02_Test_02" PRIVATE ${PATTERNS_LIBS})

file(COPY assets DESTINATION .)
