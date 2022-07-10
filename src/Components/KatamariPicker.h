#pragma once
#include "../Core/ComponentBase.h"

class SphereCollider;

class KatamariPicker : public ComponentBase
{
public:
    KatamariPicker() : ComponentBase()  {}

    void Awake() override;
    void Update(float deltaTime) override;

private:
    SphereCollider* self_collider;
    std::vector<SphereCollider*> colliders_;
};
