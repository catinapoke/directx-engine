#include "SphereCollider.h"
#include "TransformComponent.h"

SphereCollider::SphereCollider(float radius) : ComponentBase(), transform_(nullptr), radius_(radius)
{
}

void SphereCollider::Awake()
{
    ComponentBase::Awake();
    transform_ = GetActor()->GetComponent<TransformComponent>();
}

bool SphereCollider::IsOverlapping(SphereCollider& collider) const
{
    const float distance_sqr = (collider.transform_->GetWorldPosition() - transform_->GetWorldPosition()).LengthSquared();
    return distance_sqr < pow(collider.radius_ + radius_, 2);
}
