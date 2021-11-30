
add_executable ("02_Test_02" WIN32
    "src/main.cpp"
)

target_include_directories("02_Test_02" PRIVATE ${PATTERNS_INCLUDES})

target_link_libraries("02_Test_02" PRIVATE ${PATTERNS_LIBS})

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo)
endif()
