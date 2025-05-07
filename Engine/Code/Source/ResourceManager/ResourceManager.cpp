#include "ResourceManager/ResourceManager.hpp"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager l_instance{};
    return l_instance;
}