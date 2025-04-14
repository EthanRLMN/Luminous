# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #
set(VMA_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(vulkanmemoryallocator)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSBIN_EXPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSXML_EXPORTER ON CACHE BOOL "" FORCE)
add_subdirectory(assimp)

add_subdirectory(logger)
add_subdirectory(luminousmaths)


# Set repository root for Jolt here since we can't edit and save changes made on their .Cmake file
set(PHYSICS_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/jolt/")

# Enable some performance tweaks for Jolt (Only available for computers starting from 2008+)
set(JPH_ENABLE_SSE4_1 ON CACHE BOOL "" FORCE)
set(JPH_ENABLE_AVX ON CACHE BOOL "" FORCE)
include(jolt/Jolt/Jolt.cmake) # Since Jolt doesn't use CMakeLists.txt but instead uses a .cmake file, we must include this file (it does pretty much the same thing than a CMakeLists.txt)