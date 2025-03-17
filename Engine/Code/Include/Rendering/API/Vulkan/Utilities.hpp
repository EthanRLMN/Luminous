#pragma once
#include <fstream>
#include <string>
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


static std::vector<char> ReadFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}
	const size_t fileSize = (size_t) file.tellg();
	std::vector<char> fileBuffer(fileSize);

	file.seekg(0);
	file.read(fileBuffer.data(), fileSize);
	file.close();

	return fileBuffer;
}