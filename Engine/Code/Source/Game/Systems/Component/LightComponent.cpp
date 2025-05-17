#include "Game/Systems/Component/LightComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"

void LightComponent::Update()
{
    m_lightData.m_position = p_owner->Transform()->GetGlobalPosition();
}
