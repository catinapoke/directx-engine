#include "Camera.h"
#include "TransformComponent.h"
#include "WindowApplication.h"
#include "InputDevice\SimpleMath.h"

void CameraComponent::Awake()
{
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);

    CreateProjectionMatrix();
}

Matrix CameraComponent::GetProjectionViewMatrix()
{
    Vector3 rotation = transform->GetWorldRotation();
    Vector3 position = transform->GetWorldPosition();
    Matrix rotation_matrix = Matrix::CreateFromYawPitchRoll(
        rotation.z, rotation.y, rotation.x);

    Matrix view = Matrix::CreateLookAt(
        position,
        position + rotation_matrix.Forward(),
        rotation_matrix.Up());
    return view * projection_matrix;
    //return transform->GetLocalModelMatrix() * projection_matrix;
}

void CameraComponent::CreateProjectionMatrix()
{
    float aspect_ratio = WindowApplication::GetInstance()->GetInstance()->GetAspectRatio();
    projection_matrix = Matrix::CreatePerspectiveFieldOfView(60 * M_PI / 180, aspect_ratio, 0.1, 10000);
}
