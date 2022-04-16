#pragma once
#include "ComponentBase.h"

class TransformComponent;

class SphereCollider : public ComponentBase
{
public:
    explicit SphereCollider(float radius = 1.f);

    void Awake() override;
    bool IsOverlapping(SphereCollider& collider) const;

private:
    TransformComponent* transform_;
    float radius_;
};
