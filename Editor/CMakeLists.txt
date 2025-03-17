project(Editor
        VERSION 1.0.0
        LANGUAGES CXX)



#---------------------------------------#
#                SOURCES                #
#---------------------------------------#
file(GLOB_RECURSE L_EDITOR_SOURCES "Code/*.cpp")



#---------------------------------------#
#               BUILD MODE              #
#---------------------------------------#
add_executable(L_EDITOR "main.cpp")



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#
target_include_directories(L_EDITOR PUBLIC "Code/Include")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(L_EDITOR PUBLIC cxx_std_23)

if(MSVC)
    target_compile_options(L_EDITOR PUBLIC /W3 /WX)
else()
    target_compile_options(L_EDITOR PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)



#---------------------------------------#
#        EXPORTS / IMPORTS FOR DLL      #
#---------------------------------------#
add_subdirectory(Libs)

target_link_libraries(L_EDITOR PUBLIC L_ENGINE imgui)



#---------------------------------------#
#           COPY ASSETS FOLDER          #
#---------------------------------------#
# Copy resources dir command.
add_custom_command(
        TARGET L_EDITOR
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:L_EDITOR>/Assets
)