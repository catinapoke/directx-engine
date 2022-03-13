#include "Camera.h"
#include "TransformComponent.h"
#include "WindowApplication.h"

void CameraComponent::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);
    CreateProjectionMatrix();
}

Matrix CameraComponent::GetProjectionViewMatrix()
{
    return transform->GetLocalModelMatrix() * projection_matrix;
}

void CameraComponent::CreateProjectionMatrix()
{
    float aspect_ratio = WindowApplication::GetInstance()->GetInstance()->GetAspectRatio();
    projection_matrix = Matrix::CreatePerspectiveFieldOfView(60, aspect_ratio, 0.1, 100);
}
