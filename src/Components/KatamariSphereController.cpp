#include "KatamariSphereController.h"

#include <iostream>

#include "TransformComponent.h"
#include "Camera.h"

typedef DirectX::SimpleMath::Matrix Matrix;

KatamariSphereController::KatamariSphereController(std::shared_ptr<InputDevice> device, CameraComponent* camera)
    : transform(nullptr), camera_(camera->GetActor()->GetComponent<TransformComponent>())
{
    input_device = device;
}

void KatamariSphereController::Awake()
{
    ComponentBase::Awake();
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);
}

void RotateMatrix(TransformComponent* transform, const Vector3 rotation)
{
    if (rotation == Vector3{ 0,0,0 }) return;

    Matrix model = Matrix::CreateScale(transform->GetLocalScale());
    model *= Matrix::CreateFromQuaternion(transform->GetLocalQuaternion());
    //model *= Matrix::CreateFromQuaternion(Quaternion::CreateFromYawPitchRoll(rotation.z, rotation.y, rotation.x));
    model *= Matrix::CreateRotationX(rotation.x);
    model *= Matrix::CreateRotationY(rotation.y);
    model *= Matrix::CreateRotationZ(rotation.z);
    model *= Matrix::CreateTranslation(transform->GetLocalPosition());
    transform->SetLocalMatrix(model);

    Vector3 r = transform->GetLocalRotation();
    std::cout << "R: " << r.x << " " << r.y << " " << r.z << std::endl;
}

void KatamariSphereController::Update(float deltaTime)
{
    ComponentBase::Update(deltaTime);

    Vector3 position = transform->GetLocalPosition();
    Vector3 rotation = transform->GetLocalRotation();

    const Vector3 move_direction = GetMoveDirection();
    position += move_direction * direction_weight * deltaTime;
    transform->SetLocalPosition(position);

    rotation = CircleRotation(rotation + GetRotationOffset(move_direction) * rotation_weight * deltaTime);
    transform->SetLocalRotation(rotation);

    // RotateMatrix(transform, GetRotationOffset(move_direction) * rotation_weight * deltaTime);
}

Vector3 KatamariSphereController::GetMoveDirection() const
{
    Vector3 direction(0, 0, 0);

    if (input_device->IsKeyDown(Keys::D)) {
        direction += Vector3(1.0f, 0.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::A)) {
        direction += Vector3(-1.0f, 0.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::W)) {
        direction += Vector3(0.0f, 0.0f, 1.0f);
    }
    if (input_device->IsKeyDown(Keys::S)) {
        direction += Vector3(0.0f, 0.0f, -1.0f);
    }

    direction.Normalize();

    Vector3 forward = transform->GetWorldPosition() - camera_->GetWorldPosition();

    forward = (Matrix::CreateTranslation(forward) * transform->GetParentWorldModelMatrix().Invert()).Translation();
    forward.y = 0;
    forward.Normalize();

    const Vector3 right = forward.Cross(Vector3(0, 1, 0));

    return forward * direction.z + right * direction.x;
}

Vector3 KatamariSphereController::GetRotationOffset(Vector3 move_direction)
{
    move_direction.Normalize();
    return { -move_direction.x, move_direction.z,  0 };
}
