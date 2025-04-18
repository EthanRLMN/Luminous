#pragma once

#include <string>

class IResourceManager;
class IDevice;
class ISwapChain;
class IDepthResource;
class ICommandPool;

struct IResourceParams
{
    IDevice* m_device { nullptr };
    ISwapChain* m_swapChain { nullptr };
    IDepthResource* m_depthResource { nullptr };
    ICommandPool* m_commandPool { nullptr };

    //TODO: Add default values as a backup to avoid potential issues
    std::string m_meshPath;
    std::string m_texturePath;
    std::string m_vertexShaderPath;
    std::string m_fragmentShaderPath;
    std::string m_tesselationShaderPath;
    std::string m_geometryShaderPath;
};


class IResource
{
public:
	IResource() = default;
    virtual ~IResource() = default;

	virtual bool Create(IResourceManager* a_manager, const IResourceParams& a_params) = 0;
    virtual void Destroy(IDevice* a_device) = 0;
    [[nodiscard]] virtual bool IsLoaded() const { return m_isLoaded; }
    virtual void SetLoaded(const bool a_loaded) { m_isLoaded = a_loaded; }

private:
    bool m_isLoaded = false;
};


