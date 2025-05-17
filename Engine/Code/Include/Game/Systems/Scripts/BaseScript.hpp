
#pragma once

#include <memory>

#include "ResourceManager/Resource.hpp"
#include "Logger.hpp"

class Entity;

class BaseScript
{
public:
	std::shared_ptr<Entity> m_owner;


	virtual void Init()
	{
	    //Gameplay Starts
        DEBUG_LOG_INFO("Base Script game start");
	};
    virtual void Update()
    {
        //Update
        DEBUG_LOG_INFO("Base Script update");
    };

};
