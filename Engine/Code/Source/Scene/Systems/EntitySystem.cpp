#include <ranges>

#include "Scene/Systems/EntitySystem.hpp"

void EntitySystem::Update()
{
    for (const auto& l_component : std::views::values(m_components))
        l_component->Update();
}
