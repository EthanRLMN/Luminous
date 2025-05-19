#pragma once

#include <memory>

#include "Logger.hpp"

class Entity;

class BaseScript
{
public:
    virtual ~BaseScript() = default;
    std::shared_ptr<Entity> m_owner;


	virtual void Init() = 0;
    virtual void Update() = 0;

};
