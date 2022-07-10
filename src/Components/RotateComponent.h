#pragma once
#include "../Core/ComponentBase.h"

class Actor;
class TransformComponent;

class RotateComponent : public ComponentBase
{
public:
    RotateComponent() : transform(nullptr) {}

    void Awake() override;
    void Update(float deltaTime) override;

private:
    TransformComponent* transform;
};