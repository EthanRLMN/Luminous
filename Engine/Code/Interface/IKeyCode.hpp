#pragma once

#include <iostream>
#include <string>
#include "Exporter.hpp"




class LUMINOUS_ENGINE_API IKeycode
{
public:
    IKeycode() = default;

    int E() { return GLFW_KEY_E; };

    inline static int A = GLFW_KEY_A;

private:

};