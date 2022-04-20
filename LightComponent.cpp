#include "LightComponent.h"
#include "TransformComponent.h"

void LightComponent::Awake()
{
    ComponentBase::Awake();
    transform_ = GetActor()->GetComponent<TransformComponent>();
}

DirectX::SimpleMath::Vector4 LightComponent::GetColor()
{
    return color_;
}

DirectX::SimpleMath::Vector3 LightComponent::GetDirection()
{
    return transform_->GetForward();
}

DirectX::SimpleMath::Vector3 LightComponent::GetPosition()
{
    return transform_->GetWorldPosition();
}
