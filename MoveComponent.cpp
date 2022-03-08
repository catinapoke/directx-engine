#include "MoveComponent.h"

#include <iostream>

MoveComponent::MoveComponent(SceneComponent* component)
{
    transformComponent = component;
}

void MoveComponent::Update(float deltaTime)
{
    Vector4 position = transformComponent->GetPosition();
    transformComponent->SetPosition(position + Vector4(velocity.x * deltaTime, velocity.y * deltaTime, 0, 0));
}

void MoveComponent::SetVelocity(Vector2 velocity)
{
    this->velocity = velocity;
}
