#pragma once
#include "../InputDevice/SimpleMath.h"
#include "../Core/ComponentBase.h"
#include "../Core/Actor.h"

typedef DirectX::SimpleMath::Vector4 Vector4;
typedef DirectX::SimpleMath::Matrix Matrix;

class TransformComponent;

class CameraComponent : public ComponentBase
{
public:
    CameraComponent() :transform(nullptr) {}

    void Awake() override;
    Matrix GetProjectionViewMatrix() const;
    Matrix GetProjectionMatrix() const { return projection_matrix; }
    Matrix CreateOrtoProjectionMatrix() const;


private:
    void CreateProjectionMatrix();

private:
    Matrix projection_matrix;
    TransformComponent* transform;
};