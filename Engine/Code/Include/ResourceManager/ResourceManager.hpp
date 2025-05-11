#pragma once
#include <unordered_map>

#include "Resource.hpp"
#include "ResourceContext.hpp"
#include "Resources/ModelLoading/AssimpModelLoader.hpp"


class ResourceManager
{
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    static ResourceManager& GetInstance();

    inline void Init() { m_meshLoader = new AssimpModelLoader(); }
    static void Destroy(IDevice* a_device);

	template<typename T> T* LoadResource(const IResourceParams& a_params);
	template<typename T> T* GetResource(const std::string& a_file);
	template<typename T> void DeleteResource(const std::string& a_file,IDevice* a_device);

	[[nodiscard]] AssimpModelLoader* GetMeshLoader() const { return m_meshLoader; };

    inline void SetContext(const ResourceContext& a_context) { m_context = a_context; }
    inline const ResourceContext& GetContext() const { return m_context; }


private:
    explicit ResourceManager() = default;

    ResourceContext m_context { };
	AssimpModelLoader* m_meshLoader { nullptr };
    std::unordered_map<std::string, IResource*> m_resources{};
};


#include "ResourceManager/ResourceManager.inl"