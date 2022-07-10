#pragma once
#include <memory>
#include "../InputDevice/InputDevice.h"

class InputComponent
{
public:
    InputComponent() {};
    InputComponent(InputDevice* input) : inputDevice(input) {};
    virtual void HandleInput() = 0;
protected:
    InputDevice* inputDevice;
};