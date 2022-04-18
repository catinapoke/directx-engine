#include "OrbitTransformController.h"
#include "InputDevice/InputDevice.h"
#include "TransformComponent.h"
#include "SphericalCoords.h"
#include <iostream>

OrbitTransformController::OrbitTransformController(std::shared_ptr<InputDevice> device)
    : transform(nullptr), input_device(device)
{}

void OrbitTransformController::Awake()
{
    ComponentBase::Awake();
    transform = GetActor()->GetComponent<TransformComponent>();
    assert(transform != nullptr);

    coords = Cartesian2Spherical(transform->GetLocalPosition());

    std::cout << coords.radius << " " << coords.v_angle << " " << coords.h_angle << std::endl;
    Vector3 c_coords = Spherical2Cartesian(coords);
    std::cout << c_coords.x << " " << c_coords.y << " " << c_coords.z << std::endl;
}

void OrbitTransformController::Update(float deltaTime)
{
    ComponentBase::Update(deltaTime);

    // Orbit view and move

    const SphericalCoords offset = GetRotationOffset();
    const float delta = deltaTime * rotation_weight;
    coords = {
        coords.radius + offset.radius * delta,
        coords.v_angle + offset.v_angle * delta,
        coords.h_angle + offset.h_angle * delta //clamp<float>(,-M_PI / 2, M_PI / 2)
    };

    Vector3 position = Spherical2Cartesian(coords);
    transform->SetLocalPosition(position);

    transform->LookAt(Vector3(0,0,0), Vector3(0,1,0));
}

SphericalCoords OrbitTransformController::GetRotationOffset() const
{
    const DirectX::SimpleMath::Vector2 offset = input_device->GetMouseOffset();
    return { 0, -offset.x, -offset.y };
}
