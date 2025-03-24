#pragma once
#include "ResourceManager.hpp"

class Mesh : public Resource
{
public:
	Mesh() = default;
	~Mesh() = default;

	void Initialize(ResourceManager* a_manager, std::string a_file) override;
	void Destroy() override;

};