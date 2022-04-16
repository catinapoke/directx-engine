#pragma once
#include <memory>

#include "ComponentBase.h"
#include "InputDevice/SimpleMath.h"

class InputDevice;
class TransformComponent;

class OrbitTransformController : public ComponentBase
{
public:
    explicit OrbitTransformController(std::shared_ptr<InputDevice> device);

    void Awake() override;
    void Update(float deltaTime) override;

protected:
    DirectX::SimpleMath::Vector3 GetRotationOffset() const;
    DirectX::SimpleMath::Quaternion GetRotationOffsetQ(float coefficient) const;

protected:
    TransformComponent* transform;
    std::shared_ptr<InputDevice> input_device;

    const float rotation_weight = 3.0f;
};
