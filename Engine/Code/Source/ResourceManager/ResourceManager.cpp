#include "ResourceManager/ResourceManager.hpp"


ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager l_instance{};
    return l_instance;
}


void ResourceManager::Destroy(IDevice* a_device)
{
    for (const std::pair<const std::string, IResource*>& l_resource : GetInstance().m_resources)
    {
        if (l_resource.second)
        {
            l_resource.second->Destroy(a_device);
            delete (l_resource.second);
        }
    }
    delete GetInstance().m_meshLoader;
}
