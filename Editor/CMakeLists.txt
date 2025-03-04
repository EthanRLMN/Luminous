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
target_compile_features(L_EDITOR PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(L_EDITOR PUBLIC /W4 /WX)
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
target_compile_definitions(L_EDITOR PRIVATE LUMINOUS_EDITOR_EXPORTS)

add_subdirectory(Libs)

set(IMGUI_FILES_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Libs/imgui")
file(GLOB IMGUI_SOURCES_FILES "${IMGUI_FILES_LOCATION}/*.cpp" "${IMGUI_FILES_LOCATION}/backends/vulkan/imgui_impl_vulkan.cpp")

add_library(imgui STATIC ${IMGUI_SOURCES_FILES})
target_include_directories(imgui PUBLIC ${IMGUI_FILES_LOCATION})