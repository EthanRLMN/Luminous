#pragma once


class LantualVkInstance;

class Window;

class LantualInstance {
public:

	virtual void Create(Window* _window) = 0;
	virtual void Destroy() = 0;

    virtual LantualInstance* CastVulkan()
    {
        std::cout << "Wrong cast" << std::endl;
        return nullptr;
        
    }

    virtual VkInstance GetInstance() const
    {
        return nullptr;
    }

};