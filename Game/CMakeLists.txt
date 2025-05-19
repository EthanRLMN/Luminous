# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #

# Define minimum CMake version required
cmake_minimum_required(VERSION 3.20)



project(Game
        VERSION 1.0.0
        LANGUAGES CXX)



#---------------------------------------#
#                SOURCES                #
#---------------------------------------#

file(GLOB_RECURSE L_GAME_SOURCES "Code/*.cpp")



#---------------------------------------#
#            BUILD MODE                 #
#---------------------------------------#

add_library(L_GAME SHARED ${L_GAME_SOURCES})



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#

target_include_directories(L_GAME PUBLIC "Code/Include")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(L_GAME PUBLIC cxx_std_23)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    target_compile_options(L_GAME PUBLIC /W3 /WX)
else()
    target_compile_options(L_GAME PUBLIC -Wall -Wextra -Wpedantic)
endif()



# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)



#---------------------------------------#
#        EXPORTS / IMPORTS FOR DLL      #
#---------------------------------------#

# Disable lib prefix
set_target_properties(L_GAME PROPERTIES PREFIX "")

# Set dll name
set_target_properties(L_GAME PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")



target_link_libraries(L_GAME PUBLIC L_ENGINE)