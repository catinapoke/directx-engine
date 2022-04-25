#pragma once
#include <map>
#include <directxmath.h>
#include "InputDevice\Keys.h"
#include "InputComponent.h"

class InputDevice;
class MoveComponent;

class PaddleInputComponent : public InputComponent
{
public:
    PaddleInputComponent() {};
    PaddleInputComponent(InputDevice* input, MoveComponent* movement, std::map<Keys, DirectX::XMFLOAT2>& velocityMap);
    void HandleInput();

private:
    MoveComponent* moveComponent;
    std::map<Keys, DirectX::XMFLOAT2> velocity;
};


