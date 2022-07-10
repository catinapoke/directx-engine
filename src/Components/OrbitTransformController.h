#pragma once
#include <memory>

#include "../Core/ComponentBase.h"
#include "../Utils/SphericalCoords.h"

class InputDevice;
class TransformComponent;
struct SphericalCoords;

class OrbitTransformController : public ComponentBase
{
public:
    explicit OrbitTransformController(std::shared_ptr<InputDevice> device);

    void Awake() override;
    void Update(float deltaTime) override;

protected:
    SphericalCoords GetRotationOffset() const;

protected:
    TransformComponent* transform;
    std::shared_ptr<InputDevice> input_device;

    SphericalCoords coords;
    const float rotation_weight = 0.5f;
};
