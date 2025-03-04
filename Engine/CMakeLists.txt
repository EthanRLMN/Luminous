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
target_include_directories(L_ENGINE PUBLIC "Code/Include")

#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(L_ENGINE PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(L_ENGINE PUBLIC /W4 /WX)
else()
    target_compile_options(L_ENGINE PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

#---------------------------------------#
#        EXPORTS / IMPORTS FOR DLL      #
#---------------------------------------#
target_compile_definitions(L_ENGINE PRIVATE LUMINOUS_ENGINE_EXPORTS)

add_subdirectory(Libs)