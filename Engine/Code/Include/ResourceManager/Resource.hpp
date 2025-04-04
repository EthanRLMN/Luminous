#pragma once
#include <string>
#include <cstdarg>

class IResourceManager;
class IDevice;
class ISwapChain;
class IDepthResource;
class ICommandPool;

struct IResourceParams
{
    IDevice* m_device = nullptr;
    ISwapChain* m_swapChain = nullptr;
    IDepthResource* m_depthResource = nullptr;
    ICommandPool* m_commandPool = nullptr;

    std::string m_meshPath = "";
    std::string m_texturePath = "";
    std::string m_vertexShaderPath = "";
    std::string m_fragmentShaderPath = "";
};

class IResource
{
public:

	IResource() = default;
	~IResource() = default;

	virtual bool Create(IResourceManager* a_manager, IResourceParams a_params) = 0;
	virtual void Destroy(...) = 0;
    bool isLoaded = false;


};


