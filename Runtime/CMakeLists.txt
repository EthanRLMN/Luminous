# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #

# Define minimum CMake version required
cmake_minimum_required(VERSION 3.20)



project(Runtime
        VERSION 1.0.0
        LANGUAGES CXX)



#---------------------------------------#
#            BUILD MODE                 #
#---------------------------------------#

add_executable(L_RUNTIME Main.cpp)



#---------------------------------------#
#                INCLUDE                #
#---------------------------------------#

target_include_directories(L_RUNTIME PRIVATE "Engine/Code/Include" "Engine/Code/Interface")



#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(L_RUNTIME PUBLIC cxx_std_23)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    target_compile_options(L_RUNTIME PUBLIC /W3 /WX)
else()
    target_compile_options(L_RUNTIME PUBLIC -Wall -Wextra -Wpedantic)
endif()



# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)



target_link_libraries(L_RUNTIME PRIVATE L_GAME)