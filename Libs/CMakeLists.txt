# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #

# include additional CMake functions.
include(FetchContent)

if (NOT TARGET glfw)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.4
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw
    )
    FetchContent_MakeAvailable(glfw)
endif ()