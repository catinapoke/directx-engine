#include "RotateComponent.h"
#include "TransformComponent.h"
#include "../Core/Actor.h"
#include <assert.h>

float CircleValue(float value, float low, float hi);

void RotateComponent::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);
};

void RotateComponent::Update(float deltaTime)
{
    float degree = 30 * M_PI / 180;
    Vector3 rotation = transform->GetLocalRotation();

    rotation.x += deltaTime * degree;
    rotation.x = CircleValue(rotation.x, -M_PI, M_PI);
    transform->SetLocalRotation(rotation);
};

float CircleValue(float value, float low, float hi)
{
    return value - (hi - low) * trunc((value - low)/(hi - low));
}