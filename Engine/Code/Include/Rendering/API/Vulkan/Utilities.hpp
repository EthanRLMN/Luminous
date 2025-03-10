#pragma once

#include <fstream>
#include <vector>

//Indice (locations) of queue families (if they exist  at all)

struct QueueFamilyIndices
{
	int graphicsFamily{-1}; //location of graphics Queue Family
	int presentationFamily{-1}; //presentation queue family

	//check if queue families are valid
	[[nodiscard]] bool IsValid() const
	{
		return graphicsFamily >= 0 && presentationFamily >= 0;
	}
};

struct SwapChainDetails
{
	VkSurfaceCapabilitiesKHR surfaceCapabilities{}; // Suface properties , e.g. image size/extent
	std::vector<VkSurfaceFormatKHR> formats{}; //Surface image formats,e.g RGBA ansd size
	std::vector<VkPresentModeKHR> presentationModes{}; // how images should be pretend to screen
};

const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


static std::vector<char> readFile(const std::string& filename)
{
	//open stream from given file 
	//std binary  = tells stream to read file as binary
	//std ate tells stream to start reading from end of file
	std::ifstream file(filename, std::ios::binary | std::ios::ate);


	//check if file stream sucessfully opened
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}

	const size_t fileSize = (size_t) file.tellg();
	std::vector<char> fileBuffer(fileSize);

	//Move read position 
	file.seekg(0);
	//read the file data into the buffer
	file.read(fileBuffer.data(), fileSize);

	file.close();

	return fileBuffer;
}