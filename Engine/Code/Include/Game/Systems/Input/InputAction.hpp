#pragma once

#include <string>
#include <vector>


struct KeyBinding
{
    Key m_key {};
    int m_mods {};

    bool operator==(const KeyBinding& a_otherKey) const { return m_key == a_otherKey.m_key && m_mods == a_otherKey.m_mods; }
};


struct InputAction
{
    std::string m_name {"InputAction" };
    std::vector<KeyBinding> m_bindings {};
    bool m_isPressed { false };
    bool m_isDown { false };
    bool m_isReleased { false };
};