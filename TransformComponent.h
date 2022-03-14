#pragma once
#include "ComponentBase.h"
#include "InputDevice\SimpleMath.h"

#define M_PI 3.14159265358979323846

typedef DirectX::SimpleMath::Vector4 Vector4;
typedef DirectX::SimpleMath::Vector3 Vector3;
typedef DirectX::SimpleMath::Matrix Matrix; 
typedef DirectX::SimpleMath::Quaternion Quaternion;

class TransformComponent : public ComponentBase
{
public:
    TransformComponent(Actor* owner, Vector3 start_position = Vector3(0, 0, 0), 
        Vector3 start_rotation = Vector3(0, 0, 0),
        Vector3 start_scale = Vector3(1, 1, 1),
        TransformComponent* parentNode = nullptr)
        :ComponentBase(owner)
    {
        parent = parentNode;
        position = start_position;
        rotation = start_rotation;
        scale = start_scale;
        modelMatrix = CreateLocalModelMatrix();
    }

    TransformComponent* GetParent() { return parent; }

    Vector3 GetLocalPosition() { return position; }
    Vector3 GetLocalRotation() { return rotation; }
    Vector3 GetLocalScale() { return scale; }

    Vector3 GetWorldPosition();
    Vector3 GetWorldRotation();
    Vector3 GetWorldScale();

    void SetLocalPosition(Vector3 value);
    void SetLocalRotation(Vector3 value);
    void SetLocalScale(Vector3 value);

    Matrix GetLocalModelMatrix();
    Matrix GetWorldModelMatrix();

    void SetLocalMatrix(Matrix model);

    void LookAt(Vector3 targetPosition, Vector3 worldUp);

private:
    Matrix CreateLocalModelMatrix();
    Matrix CreateWorldModelMatrix();

    void UpdateMatrixFromData();
    void UpdateDataFromMatrix();

private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Matrix modelMatrix;
    TransformComponent* parent;
};