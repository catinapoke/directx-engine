#pragma once
#include "ComponentBase.h"
#include "InputDevice/SimpleMath.h"

class TransformComponent;
typedef DirectX::SimpleMath::Vector4 Vector4;

class LightComponent : public ComponentBase
{
public:
    LightComponent(Vector4 color = {0,0,0,0}):ComponentBase(), color_(color) {}

    void Awake() override;

    DirectX::SimpleMath::Vector4 GetColor();
    DirectX::SimpleMath::Vector3 GetDirection();
    DirectX::SimpleMath::Vector3 GetPosition();

private:
    DirectX::SimpleMath::Vector4 color_;
    TransformComponent* transform_;
};
