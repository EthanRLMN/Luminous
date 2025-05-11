#include "ResourceManager/ResourceManager.hpp"

#include <ranges>


ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager l_instance{};
    return l_instance;
}


void ResourceManager::Destroy(IDevice* a_device)
{
    for (IResource* const& l_resource : GetInstance().m_resources | std::views::values)
    {
        if (l_resource)
        {
            l_resource->Destroy(a_device);
            delete (l_resource);
        }
    }
    delete GetInstance().m_meshLoader;
}
