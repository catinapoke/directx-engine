#pragma once
#include "ComponentBase.h"
#include <random>
#include "InputDevice/SimpleMath.h"

class Actor;
class TransformComponent;

typedef DirectX::SimpleMath::Vector3 Vector3;

class OrbitRotator : public ComponentBase
{
public:
    OrbitRotator() : transform(nullptr), speed(rand() % 10) {}

    void Awake() override;
    void Update(float deltaTime) override;

private:
    Vector3 rotation;
    TransformComponent* transform;
    float speed = 1;
};