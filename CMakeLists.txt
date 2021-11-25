
cmake_minimum_required (VERSION 3.20)
project ("interactive-game-programming-patterns")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED true)

# Generate compile_commands.json
set (CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package (SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package (ImGui CONFIG REQUIRED)
find_package (ImGui-SFML CONFIG REQUIRED)

add_subdirectory ("Patterns")

# Copy the ./LICENSE to the ${CMAKE_BINARY_DIR}
file (COPY "LICENSE" DESTINATION ${CMAKE_BINARY_DIR})

# Copy the third-party license files to the ${CMAKE_BINARY_DIR}/licenses
set (share_dir "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/share")
file (GLOB children RELATIVE ${share_dir} "${share_dir}/*")
foreach (child ${children})
    if (IS_DIRECTORY "${share_dir}/${child}")
        if (EXISTS "${share_dir}/${child}/copyright")
            file (COPY "${share_dir}/${child}/copyright"
                  DESTINATION "${CMAKE_BINARY_DIR}/licenses")
            file (RENAME "${CMAKE_BINARY_DIR}/licenses/copyright"
                         "${CMAKE_BINARY_DIR}/licenses/${child}.license.txt")
        endif()
    endif()
endforeach()
