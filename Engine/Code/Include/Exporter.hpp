#pragma once

#ifdef LUMINOUS_ENGINE_EXPORTS
    #define LUMINOUS_ENGINE_API __declspec(dllexport)
#else
    #define LUMINOUS_ENGINE_API __declspec(dllimport)
#endif
