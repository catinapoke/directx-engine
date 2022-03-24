#pragma once
#include "InputDevice\SimpleMath.h"
#include "ComponentBase.h"
#include "Actor.h"

typedef DirectX::SimpleMath::Vector4 Vector4;
typedef DirectX::SimpleMath::Matrix Matrix;

class TransformComponent;

class CameraComponent : public ComponentBase
{
public:
    CameraComponent() :transform(nullptr) {}

    void Awake() override;
    Matrix GetProjectionViewMatrix();

private:
    void CreateProjectionMatrix();

private:
    Matrix projection_matrix;
    TransformComponent* transform;
};