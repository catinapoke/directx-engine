#include "TransformComponent.h"

// TODO: add parent logic
Vector3 TransformComponent::GetWorldPosition()
{
    return GetLocalPosition();
}

Vector3 TransformComponent::GetWorldRotation()
{
    return GetWorldRotation();
}

Vector3 TransformComponent::GetWorldScale()
{
    return GetLocalScale();
}

void TransformComponent::SetLocalPosition(Vector3 value)
{
    position = value;
    modelMatrix = CreateLocalModelMatrix();
}

void TransformComponent::SetLocalRotation(Vector3 value)
{
    rotation = value;
    modelMatrix = CreateLocalModelMatrix();
}

void TransformComponent::SetLocalScale(Vector3 value)
{
    scale = value;
    modelMatrix = CreateLocalModelMatrix();
}

Matrix TransformComponent::CreateLocalModelMatrix()
{
    Matrix matrix = Matrix::CreateScale(scale);
    matrix *= Matrix::CreateFromQuaternion(Quaternion(rotation, 1));
    matrix *= Matrix::CreateTranslation(position);
    return matrix;
}

Matrix TransformComponent::CreateWorldModelMatrix()
{
    return CreateLocalModelMatrix();
}

Matrix TransformComponent::GetLocalModelMatrix()
{
    return modelMatrix;
}

Matrix TransformComponent::GetWorldModelMatrix()
{
    return GetLocalModelMatrix();
}

void TransformComponent::LookAt(Vector4 targetPosition, Vector4 worldUp)
{
    modelMatrix = Matrix::CreateLookAt(position, (Vector3)targetPosition, (Vector3)worldUp);
    Quaternion quaternion;
    modelMatrix.Decompose(position, quaternion, scale);
    rotation = quaternion.ToEuler();
}
