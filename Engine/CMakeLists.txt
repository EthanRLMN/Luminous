project(Engine
        VERSION 1.0.0
        LANGUAGES CXX)



# --------------------------------------- #
#              FIND PACKAGES              #
# --------------------------------------- #
add_subdirectory(Libs)

find_package(Vulkan 1.4.304 REQUIRED)



#---------------------------------------#
#                SOURCES                #
#---------------------------------------#
file(GLOB_RECURSE L_ENGINE_SOURCES "Code/*.cpp")



#---------------------------------------#
#            BUILD MODE                 #
#---------------------------------------#
add_library(L_ENGINE SHARED ${L_ENGINE_SOURCES})



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#
target_include_directories(L_ENGINE PUBLIC "Code/Include" "Code/Interface" "Libs/stb_image")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(L_ENGINE PUBLIC cxx_std_23)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    target_compile_options(L_ENGINE PUBLIC /W3 /WX)
else()
    target_compile_options(L_ENGINE PUBLIC -Wall -Wextra -Wpedantic)
endif()

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

target_link_libraries(L_ENGINE PUBLIC Vulkan::Vulkan glfw L_LOGGER L_MATHS)



#---------------------------------------#
#        EXPORTS / IMPORTS FOR DLL      #
#---------------------------------------#
target_compile_definitions(L_ENGINE PRIVATE LUMINOUS_ENGINE_EXPORTS)

# Disable lib prefix
set_target_properties(L_ENGINE PROPERTIES PREFIX "")

# Set dll name
set_target_properties(L_ENGINE PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")



#---------------------------------------#
#           COPY ASSETS FOLDER          #
#---------------------------------------#
# Copy resources dir command.
add_custom_command(
        TARGET L_ENGINE
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:L_ENGINE>/Assets
)