#include <assert.h>
#include "TransformController.h"
#include "TransformComponent.h"
#include "Actor.h"
#include "InputDevice\Keys.h"

float CircleFloat(float value, float low, float hi);
Vector3 CircleRotation(Vector3 rotation);
static constexpr float rotation_weight = 0.3f;
static constexpr float direction_weight = 2.5f;

void TransformController::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);
}

void TransformController::Update(float deltaTime)
{
    Vector3 position = transform->GetLocalPosition();
    Vector3 rotation = transform->GetLocalRotation();

    position += GetDirection() * direction_weight * deltaTime;
    rotation = CircleRotation(rotation + GetRotation() * rotation_weight * deltaTime);

    transform->SetLocalPosition(position);
    transform->SetLocalRotation(rotation);
}

Vector3 TransformController::GetDirection() {
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

#include <cmath>
Vector3 TransformController::GetRotation()
{
    Vector2 new_position = input_device->MousePosition;
    Vector2 offset = new_position - last_mouse_position;
    last_mouse_position = new_position;

    Vector2 size = WindowApplication::GetInstance()->GetWindowSize();
    offset.x = abs(offset.x) >= size.x - 1 ? 0 : offset.x;
    offset.y = abs(offset.y) >= size.y - 1 ? 0 : offset.y;

    return Vector3(offset.x, 0, offset.y);
}

float CircleFloat(float value, float low, float hi)
{
    return value - (hi - low) * trunc((value - low) / (hi - low));
}

Vector3 CircleRotation(Vector3 rotation)
{
    rotation.x = CircleFloat(rotation.x, -M_PI, M_PI);
    rotation.y = CircleFloat(rotation.y, -M_PI, M_PI);
    rotation.z = CircleFloat(rotation.z, -M_PI, M_PI);
    return rotation;
}