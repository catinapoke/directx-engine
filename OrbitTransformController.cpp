#include "OrbitTransformController.h"
#include "InputDevice/InputDevice.h"
#include "TransformComponent.h"

OrbitTransformController::OrbitTransformController(std::shared_ptr<InputDevice> device)
    : transform(nullptr), input_device(device)
{}

void OrbitTransformController::Awake()
{
    ComponentBase::Awake();
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);
}

void OrbitTransformController::Update(float deltaTime)
{
    ComponentBase::Update(deltaTime);

    // TODO: orbit view and move
    // Get position
    // Calculate current yaw pitch roll
    // Add offset
    // Set new location
    // Apply look at parent

    Vector3 rotation = transform->GetLocalRotation();

    rotation = CircleRotation(rotation + GetRotationOffset() * rotation_weight * deltaTime);

    transform->SetLocalRotation(rotation);
}

DirectX::SimpleMath::Vector3 OrbitTransformController::GetRotationOffset() const
{
    const DirectX::SimpleMath::Vector2 offset = input_device->GetMouseOffset();
    return { 0, -offset.y, -offset.x };
}
