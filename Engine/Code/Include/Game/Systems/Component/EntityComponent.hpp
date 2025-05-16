#pragma once

#include <memory>

class Engine;
#include <algorithm>
#include <vector>
class Entity;

class EntityComponent
{
public:
    virtual ~EntityComponent() = default;
    virtual void Initialize() = 0;
    virtual void GameplayStarted() = 0;
    virtual void Update() = 0;

    /*          Getters         */
    inline void SetEngine(Engine* a_engine) { m_engine = a_engine; }
    inline virtual void SetOwner(const std::shared_ptr<Entity>& a_relatedEntity) { p_owner = a_relatedEntity; }


    /*          Setters         */
    [[nodiscard]] inline virtual std::shared_ptr<Entity> GetOwner() const { return p_owner; }
    [[nodiscard]] inline Engine* GetEngine() const { return m_engine; }


protected:
    std::shared_ptr<Entity> p_owner {};


private:
    //std::weak_ptr<Entity> m_entity2{};
    Engine* m_engine { nullptr };
};