#include "RotateComponent.h"
#include "TransformComponent.h"
#include "Actor.h"
#include <assert.h>
#include <iostream>

void RotateComponent::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
};

void RotateComponent::Update(float deltaTime)
{
    Vector3 rotation = transform->GetLocalRotation();
    rotation.x += deltaTime * 30 * M_PI / 180;
    if (rotation.x > M_PI)
        rotation.x -= 2 * M_PI;

    transform->SetLocalRotation(rotation);
};