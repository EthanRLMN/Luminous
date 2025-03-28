#include "Game/Systems/Entity.hpp"

void Entity::Update()
{
    for (const auto& l_component : std::views::values(m_components))
        l_component->Update();
}
