#include "LightComponent.h"
#include "TransformComponent.h"

void LightComponent::Awake()
{
    ComponentBase::Awake();
    transform_ = GetActor()->GetComponent<TransformComponent>();
    orthogonal_projection = DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 30.0f);
}

DirectX::SimpleMath::Vector4 LightComponent::GetColor() const
{
    return color_;
}

DirectX::SimpleMath::Vector3 LightComponent::GetDirection() const
{
    return transform_->GetForward();
}

DirectX::SimpleMath::Vector3 LightComponent::GetPosition() const
{
    return transform_->GetWorldPosition();
}

DirectX::SimpleMath::Matrix LightComponent::GetViewMatrix() const
{
    return transform_->GetViewMatrix();
}

DirectX::SimpleMath::Matrix LightComponent::GetOrthoProjectionMatrix() const
{
    return orthogonal_projection;
}

DirectX::SimpleMath::Matrix LightComponent::GetProjectionViewMatrix() const
{
    return GetViewMatrix() * GetOrthoProjectionMatrix();
}

TransformComponent* LightComponent::GetTransform() const
{
    return transform_;
}
