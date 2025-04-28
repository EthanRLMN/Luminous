#pragma once
#include "IInputManager.hpp"
#include "Camera.hpp"


class CameraEditor : public Camera
{
public:
    CameraEditor() = default;
    ~CameraEditor() = default;

    void Init(IWindow* a_window, float a_aspectRatio, float a_fov, float a_nearPlane, float a_farPlane);
    void Update();

    void UpdateInput(IWindow* a_window, IInputManager* a_input);

    [[nodiscard]] float GetMovementSpeed() const { return m_movementSpeed; }

    void SetAspectRatio(const float a_ratio) { aspectRatio = a_ratio; };

    Maths::Matrix4 m_projectionMatrix { Maths::Matrix4::identity };
    Maths::Matrix4 m_viewMatrix { Maths::Matrix4::identity };

private:
    void MovementCamera(IWindow* a_window, IInputManager* a_input,float a_movementSpeed);
    void TurnCamera(IWindow* a_window, IInputManager* a_input, float a_movementSpeed);
    void SpeedCamera(IWindow* a_window, IInputManager* a_input, float a_cameraSpeed, float& a_movementSpeed);

    Maths::Vector3 m_camEditorPosition { Maths::Vector3(2.0f, 2.0f, 2.0f) };
    Maths::Vector3 m_camEditorDirection { Maths::Vector3::One };
    Maths::Vector3 m_camEditorUp { Maths::Vector3::ZAxis };

    float m_movementSpeed { 1.0f };
    float m_cameraTurnSpeed{ 1.0f };
    float m_cameraSpeed{ 0.1f };
};

