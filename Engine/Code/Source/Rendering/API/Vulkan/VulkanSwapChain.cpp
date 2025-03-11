#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"

#include "../../../../Interface/IDevice.hpp"

void VulkanSwapChain::Create(IWindow* a_window, IDevice* a_device, ISurface* a_surface)
{
	std::cout << "SwapChain\n";
}

void VulkanSwapChain::Destroy(IDevice* a_device)
{
	std::cout << "DestroySwapChain\n";
}
