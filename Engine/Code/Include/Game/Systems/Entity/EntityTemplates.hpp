#pragma once

class EntityTemplates
{
public:
    EntityTemplates() = default;
    ~EntityTemplates() = default;

    void RegisterEntityTemplates();


private:
    static void DefaultEmpty();
    static void DefaultPlane();
    static void DefaultCube();
    static void DefaultSphere();
    static void DefaultCapsule();
    static void DefaultCylinder();
    static void DefaultCone();
    static void DefaultMonkey();
    static void DefaultCompanion();
};