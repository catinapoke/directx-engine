#include "TransformComponent.h"

// TODO: add parent logic
Vector3 TransformComponent::GetWorldPosition()
{
    return GetWorldModelMatrix().Translation();
}

Vector3 TransformComponent::GetWorldRotation()
{
    Quaternion quaternion;
    Vector3 world_position, world_scale;
    GetWorldModelMatrix().Decompose(world_position, quaternion, world_scale);
    return quaternion.ToEuler();
}

Vector3 TransformComponent::GetWorldScale()
{
    Quaternion quaternion;
    Vector3 world_position, world_scale;
    GetWorldModelMatrix().Decompose(world_position, quaternion, world_scale);
    return world_scale;
}

void TransformComponent::SetLocalPosition(Vector3 value)
{
    position = value;
    UpdateMatrixFromData();
}

void TransformComponent::SetLocalRotation(Vector3 value)
{
    rotation = value;
    UpdateMatrixFromData();
}

void TransformComponent::SetLocalScale(Vector3 value)
{
    scale = value;
    UpdateMatrixFromData();
}

Matrix TransformComponent::CreateLocalModelMatrix()
{
    Matrix matrix = Matrix::Identity;
    matrix *= Matrix::CreateScale(scale);
    Quaternion q = Quaternion::CreateFromYawPitchRoll(rotation.z, rotation.y, rotation.x);
    matrix *= Matrix::CreateFromQuaternion(q);
    matrix *= Matrix::CreateTranslation(position);
    return matrix;
}

Matrix TransformComponent::CreateWorldModelMatrix()
{
    Matrix matrix = CreateLocalModelMatrix();
    if(parent != nullptr)
        matrix *= parent->CreateWorldModelMatrix();
    return matrix;
}

void TransformComponent::UpdateMatrixFromData()
{
    modelMatrix = CreateLocalModelMatrix();
}

void TransformComponent::UpdateDataFromMatrix()
{
    Quaternion quaternion;
    modelMatrix.Decompose(position, quaternion, scale);
    rotation = quaternion.ToEuler();
}

Matrix TransformComponent::GetLocalModelMatrix()
{
    return modelMatrix;
}

Matrix TransformComponent::GetWorldModelMatrix()
{
    Matrix matrix = GetLocalModelMatrix();
    if (parent != nullptr)
        matrix *= parent->GetWorldModelMatrix();
    return matrix;
}

void TransformComponent::SetLocalMatrix(Matrix model)
{
    modelMatrix = model;
    UpdateDataFromMatrix();
}

void TransformComponent::LookAt(Vector3 targetPosition, Vector3 worldUp)
{
    modelMatrix = Matrix::CreateLookAt(position, targetPosition, worldUp);
    UpdateDataFromMatrix();
}
