#pragma once
class Engine;

class EntityComponent
{
public:
    virtual ~EntityComponent() = default;
    virtual void Initialize() = 0;
    virtual void GameplayStarted() = 0;
    virtual void Update() = 0;

    void SetEngine(Engine* a_engine) { m_engine = a_engine; }
    [[nodiscard]] Engine* GetEngine() const { return m_engine; }


private:
    Engine* m_engine { nullptr };
};