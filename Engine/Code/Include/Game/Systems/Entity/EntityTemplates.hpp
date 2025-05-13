#pragma once

class EntityTemplates
{
public:
    EntityTemplates() = default;
    ~EntityTemplates() = default;

    void RegisterEntityTemplates();
private:
    void Empty();
    void Plane();
    void Cube();
    void Sphere();
    void Capsule();
    void Cylinder();
    void Cone();
    void Monkey();
    void Companion();
};