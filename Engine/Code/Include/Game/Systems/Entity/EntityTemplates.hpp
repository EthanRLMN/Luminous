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
    void DefaultCapsule();
    void DefaultCylinder();
    void DefaultCone();
    void DefaultMonkey();
    void DefaultCompanion();
};