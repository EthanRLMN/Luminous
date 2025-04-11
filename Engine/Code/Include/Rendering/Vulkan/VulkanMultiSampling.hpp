
#include "Interface/IMultiSampling.hpp"


class VulkanMultiSampling : public IMultiSampling
{
public:
    void Create(IDevice* a_device) override;
    void Destroy(IDevice* a_device) override;
};
