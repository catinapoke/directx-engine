#include "TransformController.h"
#include <cassert>
#include "../Core/Actor.h"
#include "TransformComponent.h"
#include "../InputDevice/Keys.h"

void TransformController::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);
}

void TransformController::Update(float deltaTime)
{
    Vector3 position = transform->GetLocalPosition();
    Vector3 rotation = transform->GetLocalRotation();

    position += GetMoveDirection() * direction_weight * deltaTime;
    rotation = CircleRotation(rotation + GetRotationOffset() * rotation_weight * deltaTime);

    transform->SetLocalPosition(position);
    transform->SetLocalRotation(rotation);
}

Vector3 TransformController::get_input_direction() const
{
    Vector3 direction(0, 0, 0);

    if (input_device->IsKeyDown(Keys::D)) {
        direction += Vector3(1.0f, 0.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::A)) {
        direction += Vector3(-1.0f, 0.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::W)) {
        direction += Vector3(0.0f, 0.0f, -1.0f);
    }
    if (input_device->IsKeyDown(Keys::S)) {
        direction += Vector3(0.0f, 0.0f, 1.0f);
    }
    if (input_device->IsKeyDown(Keys::Space)) {
        direction += Vector3(0.0f, 1.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::Z) || input_device->IsKeyDown(Keys::RightShift)) {
        direction += Vector3(0.0f, -1.0f, 0.0f);
    }

    direction.Normalize();
    return direction;
}

Vector3 TransformController::GetMoveDirection() const
{
    Vector3 direction = get_input_direction();
    const float yaw = transform->GetLocalRotation().z;
    direction = (
        Matrix::CreateTranslation(direction) * 
        Matrix::CreateFromQuaternion(Quaternion::CreateFromYawPitchRoll(yaw, 0, 0))
        ).Translation();
    return direction;
}

Vector3 TransformController::GetRotationOffset() const
{
    const Vector2 offset = input_device->GetMouseOffset();
    return {0, -offset.y, -offset.x};
}