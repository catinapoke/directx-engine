#pragma once
#include "ComponentBase.h"
#include "UtilityFunctions.h"

class TransformComponent;

class SphereCollider : public ComponentBase
{
public:
    explicit SphereCollider(float radius = 1.f);

    void Awake() override;
    bool IsOverlapping(SphereCollider& collider) const;
    void AppendRadiusByArea(const SphereCollider& collider);

    float GetRadius() const { return radius_; }

    static float GetAreaByRadius(float radius) { return 4 * M_PI * pow(radius, 3) / 3; }
    static float GetRadiusByArea(float area) { return cbrt(3 * area / (4 * M_PI)); }

private:
    TransformComponent* transform_;
    float radius_;
};
