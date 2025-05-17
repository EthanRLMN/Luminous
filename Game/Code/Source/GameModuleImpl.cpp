#include "GameModuleImpl.hpp"

#include "Logger.hpp"


void GameModuleImpl::Start()
{
    DEBUG_LOG_INFO("GAME STARTED!");
}


void GameModuleImpl::Update()
{
}


void GameModuleImpl::LateUpdate()
{
}


void GameModuleImpl::FixedUpdate()
{
}


void GameModuleImpl::End()
{
    DEBUG_LOG_INFO("GAME ENDED!");
}


extern "C" __declspec(dllexport) IGameModule* CreateGameModule() {
    return new GameModuleImpl();
}