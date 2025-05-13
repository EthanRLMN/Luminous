project(Editor
        VERSION 1.0.0
        LANGUAGES CXX)



#---------------------------------------#
#                SOURCES                #
#---------------------------------------#
file(GLOB_RECURSE L_EDITOR_SOURCES "Main.cpp" "Code/Source/*.cpp" "Libs/imgui/*.cpp" "Libs/imgui/backends/*.cpp" "Libs/imguizmo/*.cpp")

# Define the lib name for easy modification
set(LE_TARGET_NAME L_EDITOR)



#---------------------------------------#
#               BUILD MODE              #
#---------------------------------------#
add_executable(${LE_TARGET_NAME} ${L_EDITOR_SOURCES})



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#
# Both "Libs/imgui" and "Libs" folders must be included as imgui uses the path of the first one and we use the path of the second one
target_include_directories(${LE_TARGET_NAME} PUBLIC "Code/Include" "Code" "Libs/imgui" "Libs" "Libs/imguizmo")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(${LE_TARGET_NAME} PUBLIC cxx_std_23)

if(MSVC)
    target_compile_options(${LE_TARGET_NAME} PUBLIC /W3 /WX)
else()
    target_compile_options(${LE_TARGET_NAME} PUBLIC -Wall -Wextra -Wpedantic)
endif()

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${LE_TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Builds/${CMAKE_CXX_COMPILER_ID}_Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${LE_TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Builds/${CMAKE_CXX_COMPILER_ID}_Release")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set_target_properties(${LE_TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Builds/${CMAKE_CXX_COMPILER_ID}_RelWithDebInfo")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set_target_properties(${LE_TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Builds/${CMAKE_CXX_COMPILER_ID}_MinSizeRel")
endif()

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT L_EDITOR)



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
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:${LE_TARGET_NAME}>/Editor/Assets"
)

# Force copy assets folder when building for visual studio because of issues caused by single-repository project
file(COPY Assets DESTINATION "${CMAKE_BINARY_DIR}/Editor")