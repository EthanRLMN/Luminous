

class IDevice;

class IMultiSampling
{
public:
    IMultiSampling() = default;
    ~IMultiSampling() = default;

    virtual void Create(IDevice* a_device) = 0;
    virtual void Destroy(IDevice* a_device) = 0;
};
