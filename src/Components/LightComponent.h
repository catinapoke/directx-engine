#pragma once
#include "../Core/ComponentBase.h"
#include "../InputDevice/SimpleMath.h"

class TransformComponent;

class LightComponent : public ComponentBase
{
public:
    LightComponent(DirectX::SimpleMath::Vector4 color = {1, 1, 1, 1}) :ComponentBase(), color_(color) {}

    void Awake() override;

    DirectX::SimpleMath::Vector4 GetColor() const;
    DirectX::SimpleMath::Vector3 GetDirection() const;
    DirectX::SimpleMath::Vector3 GetPosition() const;
    DirectX::SimpleMath::Matrix GetViewMatrix() const;
    DirectX::SimpleMath::Matrix GetOrthoProjectionMatrix() const;
    DirectX::SimpleMath::Matrix GetProjectionViewMatrix() const;
    TransformComponent* GetTransform() const;
    
private:
    DirectX::SimpleMath::Vector4 color_;
    TransformComponent* transform_;
    DirectX::SimpleMath::Matrix orthogonal_projection;
};
