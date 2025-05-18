#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>

#ifdef ERROR
#undef ERROR
#endif

#include "Engine.hpp"
#include "IGameModule.hpp"

using CreateFunc = IGameModule* (*)();
using DestroyFunc = void (*)(IGameModule*);

int main()
{
    Engine l_engine;
    LaunchSettings l_compileLaunchSettings { true, true };
    l_engine.SetLaunchSettings(l_compileLaunchSettings);
    l_engine.Init();

    // This loads the game dll
    const HMODULE l_gameLib = LoadLibraryA("Game.dll");
    if (!l_gameLib)
    {
        DEBUG_LOG_CRITICAL("[Runtime] Failed to load Game.dll!\n");
        return -1;
    }

    const CreateFunc l_createGameModule = reinterpret_cast<CreateFunc>(GetProcAddress(l_gameLib, "CreateGameModule"));
    if (!l_createGameModule)
    {
        DEBUG_LOG_CRITICAL("[Runtime] CreateGameModule not found!\n");
        FreeLibrary(l_gameLib);
        return -2;
    }

    const DestroyFunc l_destroyGameModule = reinterpret_cast<DestroyFunc>(GetProcAddress(l_gameLib, "DestroyGameModule"));
    if (!l_destroyGameModule)
        DEBUG_LOG_WARNING("[Runtime] DestroyGameModule not found, using delete!\n");

    IGameModule* l_gameModule = l_createGameModule();

    l_gameModule->Start(); // Starts the game
    while (l_engine.IsRunning())
    {
        l_engine.Update();

        l_gameModule->Update();
    }
    l_gameModule->End();

    if (l_destroyGameModule)
        l_destroyGameModule(l_gameModule);
    else
        delete l_gameModule;

    FreeLibrary(l_gameLib);

    return 0;
}
