#include "KatamariSphereController.h"
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

void KatamariSphereController::Update(float deltaTime)
{
    ComponentBase::Update(deltaTime);

    Vector3 position = transform->GetLocalPosition();
    Vector3 rotation = transform->GetLocalRotation();

    const Vector3 move_direction = GetMoveDirection();
    position += move_direction * direction_weight * deltaTime;
    rotation = CircleRotation(rotation + GetRotationOffset(move_direction) * rotation_weight * deltaTime);

    transform->SetLocalPosition(position);
    transform->SetLocalRotation(rotation);
}

Vector3 KatamariSphereController::GetMoveDirection()
{
    Vector3 direction(0, 0, 0);

    if (input_device->IsKeyDown(Keys::D)) {
        direction += Vector3(1.0f, 0.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::A)) {
        direction += Vector3(-1.0f, 0.0f, 0.0f);
    }
    if (input_device->IsKeyDown(Keys::W)) {
        direction += Vector3(0.0f, 0.0f, -1.0f);
    }
    if (input_device->IsKeyDown(Keys::S)) {
        direction += Vector3(0.0f, 0.0f, 1.0f);
    }

    const float yaw = GetLookRotation().z;
    direction = (
        Matrix::CreateTranslation(direction) *
        Matrix::CreateFromQuaternion(Quaternion::CreateFromYawPitchRoll(yaw, 0, 0))
        ).Translation();

    direction.Normalize();
    return direction;
}

Vector3 KatamariSphereController::GetLookRotation()
{
    Vector3 scale;
    Quaternion rotation;
    Vector3 look_vector = transform->GetWorldPosition() - camera_->GetWorldPosition();

    (Matrix::CreateTranslation(look_vector) * transform->GetParentWorldModelMatrix().Invert()).Decompose(scale, rotation, look_vector);
    return rotation.ToEuler();
}

Vector3 KatamariSphereController::GetRotationOffset(Vector3 move_direction)
{
    move_direction.Normalize();
    return { -move_direction.x, move_direction.z,  0 };
}
