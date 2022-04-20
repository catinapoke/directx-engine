#pragma once
#include "ComponentBase.h"
#include "InputDevice/SimpleMath.h"

class TransformComponent;

class LightComponent : public ComponentBase
{
public:
    LightComponent(DirectX::SimpleMath::Vector4 color = {1, 1, 1, 1}) :ComponentBase(), color_(color) {}

    void Awake() override;

    DirectX::SimpleMath::Vector4 GetColor();
    DirectX::SimpleMath::Vector3 GetDirection();
    DirectX::SimpleMath::Vector3 GetPosition();

private:
    DirectX::SimpleMath::Vector4 color_;
    TransformComponent* transform_;
};
