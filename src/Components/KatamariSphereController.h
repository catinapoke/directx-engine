#pragma once
#include "TransformController.h"

class CameraComponent;

class KatamariSphereController : public ComponentBase
{
public:
    explicit KatamariSphereController(std::shared_ptr<InputDevice> device, CameraComponent* camera);

    void Awake() override;
    void Update(float deltaTime) override;

protected:
    Vector3 GetMoveDirection() const;
    Vector3 GetRotationOffset(Vector3 move_direction);

protected:
    TransformComponent* transform;
    TransformComponent* camera_;
    std::shared_ptr<InputDevice> input_device;

    const float direction_weight = 2.5f;
    const float rotation_weight = 3.0f;
};
