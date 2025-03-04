# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #

# include additional CMake functions.
include(FetchContent)

# Check if Assimp target already exists
if (NOT TARGET assimp)
    # Clone assimp repository at master and output in CMAKE_CURRENT_SOURCE_DIR location.
    FetchContent_Declare(
            assimp
            GIT_REPOSITORY https://github.com/assimp/assimp.git
            GIT_TAG v5.4.3
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assimp
    )

    # Equivalent to add_subdirectory() for fetch content.
    FetchContent_MakeAvailable(assimp)

endif ()