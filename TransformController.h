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
    }

    void Awake() override;
    void Update(float deltaTime) override;

protected:
    virtual Vector3 GetMoveDirection() const;
    Vector3 get_input_direction() const;

    Vector3 GetRotationOffset() const;

protected:
    TransformComponent* transform;
    std::shared_ptr<InputDevice> input_device;

    const float direction_weight = 2.5f;
    const float rotation_weight = 0.3f;
};