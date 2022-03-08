#pragma once
#include <d3d.h>
#include "SceneComponent.h"

typedef DirectX::SimpleMath::Vector2 Vector2;

class MoveComponent
{
public:
    MoveComponent():transformComponent(nullptr) {};
    MoveComponent(SceneComponent* component);
    void Update(float deltaTime); // move velocity * delta
    void SetVelocity(Vector2 velocity);
    Vector2 GetVelocity() { return velocity; }

private:
    Vector2 velocity;
    SceneComponent* transformComponent;
};