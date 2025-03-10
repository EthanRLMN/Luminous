#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"

#include "Rendering/IDevice.hpp"

void VulkanSwapChain::Create(Window* a_window, IDevice* a_device, ISurface* a_surface)
{
	std::cout << "SwapChain\n" << a_window << a_device << a_surface;
}

void VulkanSwapChain::Destroy(IDevice* a_device)
{
	std::cout << "DestroySwapChain\n" << a_device;
}
