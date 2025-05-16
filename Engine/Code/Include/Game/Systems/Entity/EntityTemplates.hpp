#pragma once


class EntityTemplates
{
public:
    EntityTemplates() = default;
    ~EntityTemplates() = default;

    void RegisterEntityTemplates();


private:
    void Empty();
    void Cube();
    void Plane();
    void Sphere();
    void Cone();
    void Cylinder();
    void Capsule();
    void Monkey();
    void Companion();
};