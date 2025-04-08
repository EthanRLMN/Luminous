#include "Logger.hpp"
#include "ResourceManager/Resource.hpp"
#include "Struct/VulkanUtilities.hpp"

class VulkanShader;

class IShader : public IResource
{
public:
    IShader() = default;
    ~IShader() = default;
    bool Create(IResourceManager* a_manager, IResourceParams a_params) override { return false; };
    void Destroy(IDevice* a_device) override { return; };

    virtual VulkanShader* CastVulkan()
    {
        DEBUG_LOG_ERROR("Vulkan Shader : Cast is Wrong!\n");
        return nullptr;
    }

};
