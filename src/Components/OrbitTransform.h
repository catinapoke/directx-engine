#pragma once
#include "TransformComponent.h"

class OrbitTransform : public TransformComponent
{
public:
    OrbitTransform(Vector3 start_position = Vector3(0, 0, 0),
        Vector3 start_rotation = Vector3(0, 0, 0),
        Vector3 start_scale = Vector3(1, 1, 1),
        TransformComponent* parentNode = nullptr)
            :TransformComponent(start_position, start_rotation, start_scale, parentNode)
    {}

    Matrix GetParentWorldModelMatrix() const override;
private:
    Matrix CreateParentWorldModelMatrix() const override;
    Matrix ResetRotation(Matrix origin) const;
};

inline Matrix OrbitTransform::GetParentWorldModelMatrix() const
{
    if (parent != nullptr)
        return ResetRotation(parent->GetWorldModelMatrix());
    return Matrix::Identity;
}

inline Matrix OrbitTransform::CreateParentWorldModelMatrix() const
{
    if (parent != nullptr)
        return ResetRotation(parent->CreateWorldModelMatrix());
    return Matrix::Identity;
}

inline Matrix OrbitTransform::ResetRotation(Matrix origin) const
{
    Vector3 position;
    Vector3 scale;
    Quaternion quaternion;
    origin.Decompose(scale, quaternion, position);

    return Matrix::CreateScale(scale) * Matrix::CreateTranslation(position);
}
