# --------------------------------------- #
#               CMAKE CONFIG              #
# --------------------------------------- #
set(IMGUI_FILES_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
file(GLOB IMGUI_SOURCES_FILES "${IMGUI_FILES_LOCATION}/*.cpp" "${IMGUI_FILES_LOCATION}/backends/vulkan/imgui_impl_vulkan.cpp")

add_library(imgui STATIC ${IMGUI_SOURCES_FILES})
target_include_directories(imgui PUBLIC ${IMGUI_FILES_LOCATION})