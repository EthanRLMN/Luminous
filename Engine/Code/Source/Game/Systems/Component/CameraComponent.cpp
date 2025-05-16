#include "Game/Systems/Component/CameraComponent.hpp"

#include "Engine.hpp"

void CameraComponent::Initialize() {

    m_worldForward = (m_center - m_eye).Normalize();
    m_worldRight = m_worldForward.CrossProduct(m_worldUp).Normalize();
    m_worldUp = m_worldRight.CrossProduct(m_worldForward).Normalize();

    m_projectionMatrix = UpdateProjectionMatrix(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);

    ForceSetMainCamera(false);
}

void CameraComponent::Update() {
    m_viewMatrix = UpdateViewMatrix(m_eye, m_center, m_worldUp);
}

void CameraComponent::SetMainCamera(bool a_val)
{
    /*
    std::vector<Entity*>  l_entities = GetEngine()->GetEntityManager()->GetEntitiesByComponent<CameraComponent>();
    bool l_sceneHasMain = false;
    std::vector<std::shared_ptr<Entity>> mainCamEntities;
    for (const std::shared_ptr<Entity>& entity : l_entities)
    {
        if (entity->GetComponent<CameraComponent>()->GetIsMainCamera())
        {
            DEBUG_LOG_WARNING("Scene has already a Main Camera.");
            mainCamEntities.push_back(entity);
            l_sceneHasMain = true;
            break;
        }
    }

    if (mainCamEntities.size() > 0)
    {
        if (m_mainCamera)
        {
            if (a_val == false)
            {
                DEBUG_LOG_WARNING("Cannot set Main Camera to false since its the last main camera.");
                return;
            }
        } else
        {
            if (a_val == true)
            {
                mainCamEntities[0]->GetComponent<CameraComponent>()->ForceSetMainCamera(false);
                m_mainCamera = true;
                return;
            }
        }
    } else
    {
        m_mainCamera = true;
    }*/
    

    
}

