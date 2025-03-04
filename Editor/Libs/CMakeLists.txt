# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #

# include additional CMake functions.
include(FetchContent)

# Check if imgui target already exists
if (NOT TARGET imgui)
    # Clone imgui repository at master and output in CMAKE_CURRENT_SOURCE_DIR location.
    FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG v1.91.8
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    )

    # Equivalent to add_subdirectory() for fetch content.
    FetchContent_MakeAvailable(imgui)

endif ()