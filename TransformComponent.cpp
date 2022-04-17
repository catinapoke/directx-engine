#include "TransformComponent.h"

Vector3 TransformComponent::GetWorldPosition() const
{
    return GetWorldModelMatrix().Translation();
}

Vector3 TransformComponent::GetWorldRotation() const
{
    Quaternion quaternion;
    Vector3 world_position, world_scale;
    GetWorldModelMatrix().Decompose(world_position, quaternion, world_scale);
    return quaternion.ToEuler();
}

Vector3 TransformComponent::GetWorldScale() const
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

Quaternion TransformComponent::GetLocalQuaternion() const
{
    return Quaternion::CreateFromYawPitchRoll(rotation.z, rotation.y, rotation.x);
}

Matrix TransformComponent::CreateLocalModelMatrix() const
{
    Matrix matrix = Matrix::Identity;
    matrix *= Matrix::CreateScale(scale);
    Quaternion q = GetLocalQuaternion();
    matrix *= Matrix::CreateFromQuaternion(q);
    matrix *= Matrix::CreateTranslation(position);
    return matrix;
}

Matrix TransformComponent::CreateWorldModelMatrix() const
{
    Matrix matrix = CreateLocalModelMatrix() * CreateParentWorldModelMatrix();
    return matrix;
}

Matrix TransformComponent::CreateParentWorldModelMatrix() const
{
    if (parent != nullptr)
        return parent->CreateWorldModelMatrix();
    return Matrix::Identity;
}

void TransformComponent::UpdateMatrixFromData()
{
    modelMatrix = CreateLocalModelMatrix();
}

void TransformComponent::UpdateDataFromMatrix()
{
    Quaternion quaternion;
    modelMatrix.Decompose(scale, quaternion, position);
    rotation = quaternion.ToEuler();
}

Matrix TransformComponent::GetLocalModelMatrix() const
{
    return modelMatrix;
}

Matrix TransformComponent::GetWorldModelMatrix() const
{
    Matrix matrix = GetLocalModelMatrix() * GetParentWorldModelMatrix();
    return matrix;
}

Matrix TransformComponent::GetParentWorldModelMatrix() const
{
    if (parent != nullptr)
       return parent->GetWorldModelMatrix();
    return Matrix::Identity;
}

void TransformComponent::SetParent(TransformComponent* new_parent)
{
    if (new_parent != nullptr)
    {
        modelMatrix = GetWorldModelMatrix() * new_parent->GetWorldModelMatrix().Invert();
        Matrix oop = modelMatrix * new_parent->GetWorldModelMatrix();
        Matrix oop12 = modelMatrix * new_parent->GetWorldModelMatrix();
    }
    else
    {
        modelMatrix = GetWorldModelMatrix();
    }

    UpdateDataFromMatrix();
    parent = new_parent;
}

void TransformComponent::SetLocalMatrix(Matrix model)
{
    modelMatrix = model;
    UpdateDataFromMatrix();
}

void TransformComponent::LookAt(Vector3 targetPosition, Vector3 worldUp)
{
    modelMatrix = Matrix::CreateLookAt(position, targetPosition, worldUp).Invert();
    UpdateDataFromMatrix();
}
