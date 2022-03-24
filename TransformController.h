#pragma once
#include<memory>
#include "ComponentBase.h"
#include "InputDevice\SimpleMath.h"
#include "InputDevice/InputDevice.h"

class TransformComponent;
typedef DirectX::SimpleMath::Vector3 Vector3;
typedef DirectX::SimpleMath::Vector2 Vector2;

class TransformController : public ComponentBase
{
public:
    TransformController(std::shared_ptr<InputDevice> device)
        : transform(nullptr)
    {
        input_device = device;
        last_mouse_position = input_device->MousePosition;
    }

    void Awake() override;
    void Update(float deltaTime) override;

private:
    Vector3 GetDirection();
    Vector3 GetRotation();

private:
    Vector2 last_mouse_position;
    TransformComponent* transform;
    std::shared_ptr<InputDevice> input_device;
};