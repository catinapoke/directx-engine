#pragma once
#include "ComponentBase.h"

class Actor;
class TransformComponent;

class RotateComponent : public ComponentBase
{
public:
    RotateComponent(Actor* owner) : ComponentBase(owner), transform(nullptr) {}

    void Awake() override;
    void Update(float deltaTime) override;

private:
    TransformComponent* transform;
};