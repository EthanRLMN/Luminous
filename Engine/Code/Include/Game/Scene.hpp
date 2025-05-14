#pragma once

#include "Systems/Entity/Entity.hpp"

#include <iostream>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <string>
#include <vector>

class Engine;

struct Entity_Saver
{
    //Entity
    std::string entityName;
    uint16_t entityUUID;
    bool isActive;


    //Transform Component : 
    //Transform Global
    float globalPositionX;
    float globalPositionY;
    float globalPositionZ;

    float globalRotationX;
    float globalRotationY;
    float globalRotationZ;
    float globalRotationW;

    float globalScaleX;
    float globalScaleY;
    float globalScaleZ;

    //Transform Local
    float localPositionX;
    float localPositionY;
    float localPositionZ;

    float localRotationX;
    float localRotationY;
    float localRotationZ;
    float localRotationW;

    float localScaleX;
    float localScaleY;
    float localScaleZ;


    //Model Component:

    std::string texturePath;
    std::string modelPath;

};

class Scene
{
public:
    Scene()= default;
    ~Scene()= default;

    void RegisterScene(EntityManager& a_entityManager);

    void LoadScene(std::string filename, EntityManager& a_entitymanager);
    void SaveScene(const std::string& filepath, EntityManager& a_entityManager);

    bool CheckIfFileDetected(std::string filename);

};

