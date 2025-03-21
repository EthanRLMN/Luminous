project(Editor
        VERSION 1.0.0
        LANGUAGES CXX)



#---------------------------------------#
#                SOURCES                #
#---------------------------------------#
file(GLOB_RECURSE L_EDITOR_SOURCES "main.cpp" "Code/Source/*.cpp" "Libs/imgui/*.cpp" "Libs/imgui/backends/*.cpp")

# Define the lib name for easy modification
set(LE_TARGET_NAME L_EDITOR)



#---------------------------------------#
#               BUILD MODE              #
#---------------------------------------#
add_executable(${LE_TARGET_NAME} ${L_EDITOR_SOURCES})



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#
target_include_directories(${LE_TARGET_NAME} PUBLIC "Code/Include" "Libs" "Libs/imgui")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(${LE_TARGET_NAME} PUBLIC cxx_std_23)

if(MSVC)
    target_compile_options(${LE_TARGET_NAME} PUBLIC /W3 /WX)
else()
    target_compile_options(${LE_TARGET_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(TARGET ${LE_TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${L_OUTPUT_DIR}")

#---------------------------------------#
#        EXPORTS / IMPORTS FOR DLL      #
#---------------------------------------#
add_subdirectory(Libs)

target_link_libraries(${LE_TARGET_NAME} PUBLIC L_ENGINE)



#---------------------------------------#
#           COPY ASSETS FOLDER          #
#---------------------------------------#
# Copy resources dir command.
add_custom_command(
        TARGET ${LE_TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:${LE_TARGET_NAME}>/Editor/Assets
)

# Force copy assets folder when building for visual studio because of issues caused by single-repository project
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/Editor)