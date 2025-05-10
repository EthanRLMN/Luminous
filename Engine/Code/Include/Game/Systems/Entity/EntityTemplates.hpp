#pragma once


class EntityTemplates
{
public:
    EntityTemplates() = default;
    ~EntityTemplates() = default;

    void RegisterEntityTemplates();


private:
    void RegisterEmptyEntityTemplate();
    void RegisterCubeEntityTemplate();
    void RegisterPlaneEntityTemplate();
    void RegisterSphereEntityTemplate();
};