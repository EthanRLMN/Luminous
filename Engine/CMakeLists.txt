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

# Define the lib name for easy modification
set(L_TARGET_NAME L_ENGINE)



#---------------------------------------#
#            BUILD MODE                 #
#---------------------------------------#
add_library(${L_TARGET_NAME} STATIC ${L_ENGINE_SOURCES})



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#
target_include_directories(${L_TARGET_NAME} PUBLIC "Code/Include" "Code/Interface" "Libs/stb_image" "Libs/tinyobj" "Libs/vulkanmemoryallocator/include" "Libs/glm")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(${L_TARGET_NAME} PUBLIC cxx_std_23)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    target_compile_options(${L_TARGET_NAME} PUBLIC /W3 /WX)
else()
    target_compile_options(${L_TARGET_NAME} PUBLIC -Wall -Wextra -Wpedantic)
endif()

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

target_link_libraries(${L_TARGET_NAME} PUBLIC glm::glm VulkanMemoryAllocator Vulkan::Vulkan glfw assimp L_LOGGER L_MATHS)



#---------------------------------------#
#        EXPORTS / IMPORTS FOR DLL      #
#---------------------------------------#
# Disable lib prefix
set_target_properties(${L_TARGET_NAME} PROPERTIES PREFIX "")

# Set dll name
set_target_properties(${L_TARGET_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")


#---------------------------------------#
#           COPY ASSETS FOLDER          #
#---------------------------------------#
# Copy resources dir command.
add_custom_command(
        TARGET ${L_TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        ${L_OUTPUT_DIR}/Engine/Assets
)

# Force copy assets folder when building for visual studio because of issues caused by single-repository project
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/Engine)