#include "ResourceManager/ResourceManager.hpp"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager l_instance{};
    return l_instance;
}


void ResourceManager::Destroy(IDevice* a_device)
{

    for (const auto& resource : ResourceManager::GetInstance().m_resources) 
    {
        if (resource.second) 
        {
            resource.second->Destroy(a_device);
            delete (resource.second);
        }
        
    }
    delete ResourceManager::GetInstance().m_meshLoader;
}
