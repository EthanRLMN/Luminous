#pragma once

#include "IMesh.hpp"


class VulkanMesh final : public IMesh
{
public:
    bool Create(IResourceManager* a_manager, const IResourceParams& a_params) override;
    void Destroy(IDevice* a_device) override {};
    VulkanMesh* CastVulkan() override { return this; }
};
