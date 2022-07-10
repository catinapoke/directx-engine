#include "Camera.h"
#include "TransformComponent.h"
#include "../Core/WindowApplication.h"
#include "../InputDevice\SimpleMath.h"

void CameraComponent::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);

    CreateProjectionMatrix();
}

Matrix CameraComponent::GetProjectionViewMatrix() const
{
    return transform->GetViewMatrix() * projection_matrix;
}

Matrix CameraComponent::CreateOrtoProjectionMatrix() const
{
    return DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 30.0f);
}

void CameraComponent::CreateProjectionMatrix()
{
    float aspect_ratio = WindowApplication::GetInstance()->GetInstance()->GetAspectRatio();
    projection_matrix = Matrix::CreatePerspectiveFieldOfView(60 * M_PI / 180, aspect_ratio, 0.1, 10000);
}
