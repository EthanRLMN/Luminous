#pragma once


class EntityTemplates
{
public:
    EntityTemplates() = default;
    ~EntityTemplates() = default;

    void RegisterEntityTemplates();


private:
    void DefaultEmpty();
    void DefaultPlane();
    void DefaultCube();
    void DefaultSphere();
    void Capsule();
    void Cylinder();
    void Cone();
    void Monkey();
    void DefaultCompanion();
};