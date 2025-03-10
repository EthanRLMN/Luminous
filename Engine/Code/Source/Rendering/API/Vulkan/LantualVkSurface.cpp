#include "LantualVkSurface.h"
#include "LantualVKInstance.h"

void LantualVkSurface::Create(LantualInstance* _instance, Window* _window)
{
    std::cout << "Create Surface" << std::endl;

    VkResult result = glfwCreateWindowSurface(_instance->GetInstance(), _window->m_Window, nullptr, &surface);

    if (result != VK_SUCCESS) {
        std::cerr << "Failed to create surface, error code: " << result << std::endl;
        throw std::runtime_error("failed to create surface");
    }
    std::cout << "Finish Create Surface" << std::endl;
}

void LantualVkSurface::Destroy(LantualInstance* _instance)
{
	std::cout << "Destroy Surface" << std::endl;
}
