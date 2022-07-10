#include "OrbitRotator.h"
#include "TransformComponent.h"
#include "../Core/Actor.h"
#include <assert.h>


void OrbitRotator::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);

    Vector3 position = transform->GetLocalPosition();
    rotation = position;
    rotation.Normalize();
}

void OrbitRotator::Update(float deltaTime)
{
    //Vector3  transform->GetLocalPosition()

    Matrix matrix = transform->GetLocalModelMatrix();
    
    //matrix *= Matrix::CreateFromQuaternion(speed * deltaTime * rotation);
    matrix *= Matrix::CreateRotationX(rotation.x * deltaTime * 90 * M_PI / 180);
    matrix *= Matrix::CreateRotationY(rotation.y * 0.25 * deltaTime * 90 * M_PI / 180);
    matrix *= Matrix::CreateRotationZ(rotation.z * 0.25 * deltaTime * 90 * M_PI / 180);
    transform->SetLocalMatrix(matrix);
}
