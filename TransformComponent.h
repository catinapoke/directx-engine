#pragma once
#include "ComponentBase.h"
#include "InputDevice\SimpleMath.h"

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

    void LookAt(Vector4 targetPosition, Vector4 worldUp);

private:
    Matrix CreateLocalModelMatrix();
    Matrix CreateWorldModelMatrix();

private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Matrix modelMatrix;
    TransformComponent* parent;
};