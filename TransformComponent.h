#pragma once
#include "ComponentBase.h"
#include "UtilityFunctions.h"
#include "InputDevice\SimpleMath.h"

typedef DirectX::SimpleMath::Vector4 Vector4;
typedef DirectX::SimpleMath::Vector3 Vector3;
typedef DirectX::SimpleMath::Matrix Matrix; 
typedef DirectX::SimpleMath::Quaternion Quaternion;

class TransformComponent : public ComponentBase
{
public:
    TransformComponent(Vector3 start_position = Vector3(0, 0, 0), 
        Vector3 start_rotation = Vector3(0, 0, 0),
        Vector3 start_scale = Vector3(1, 1, 1),
        TransformComponent* parentNode = nullptr)
    {
        parent = parentNode;
        position = start_position;
        rotation = start_rotation;
        scale = start_scale;
        UpdateMatrixFromData();
        //modelMatrix = CreateLocalModelMatrix();
    }

    TransformComponent* GetParent() const { return parent; }

    Vector3 GetLocalPosition() const { return position; }
    Vector3 GetLocalRotation() const { return rotation; }
    Vector3 GetLocalScale() const { return scale; }

    Vector3 GetWorldPosition() const;
    Vector3 GetWorldRotation() const;
    Vector3 GetWorldScale() const;

    void SetLocalPosition(Vector3 value);
    void SetLocalRotation(Vector3 value);
    void SetLocalScale(Vector3 value);

    Quaternion GetLocalQuaternion() const;
    Matrix GetLocalModelMatrix() const;
    Matrix GetWorldModelMatrix() const;
    Matrix GetViewMatrix() const;

    virtual Matrix GetParentWorldModelMatrix() const;

    void SetParent(TransformComponent* new_parent);

    void SetLocalMatrix(Matrix model);

    void LookAt(Vector3 targetPosition, Vector3 worldUp);

    Matrix CreateLocalModelMatrix() const;
    Matrix CreateWorldModelMatrix() const;

    Vector3 GetForward() const;

protected:
    virtual Matrix CreateParentWorldModelMatrix() const;

private:
    void UpdateMatrixFromData();
    void UpdateDataFromMatrix();

protected:
    TransformComponent* parent;

private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Matrix modelMatrix;
};