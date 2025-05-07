#pragma once

#include "IMesh.hpp"


class VulkanMesh final : public IMesh
{
public:
    bool Create(const IResourceParams& a_params) override;
    void Destroy(IDevice* a_device) override {};
    VulkanMesh* CastVulkan() override { return this; }
};
