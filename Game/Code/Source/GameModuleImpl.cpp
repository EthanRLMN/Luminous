#include "GameModuleImpl.hpp"

#include "Logger.hpp"


void GameModuleImpl::Start()
{
    DEBUG_LOG_INFO("GAME STARTED!");
}


void GameModuleImpl::Update()
{
    DEBUG_LOG_INFO("GAME UPDATE!");
}


void GameModuleImpl::LateUpdate()
{
    DEBUG_LOG_INFO("GAME LATE UPDATE!");
}


void GameModuleImpl::FixedUpdate()
{
    DEBUG_LOG_INFO("GAME FIXED UPDATE!");
}


void GameModuleImpl::End()
{
    DEBUG_LOG_INFO("GAME ENDED!");
}