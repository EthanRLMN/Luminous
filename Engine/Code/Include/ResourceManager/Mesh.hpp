#pragma once
#include "ResourceManager.hpp"
#include "ModelLoading/AssimpModelDebugger.hpp"

class Mesh : public IResource
{
public:
	Mesh() = default;
	~Mesh() = default;

	bool Initialize(IResourceManager* a_manager, std::string a_file) override;
	void Destroy() override;

	AssimpModelDebugger m_meshDebug;

};