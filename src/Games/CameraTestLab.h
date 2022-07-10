#pragma once
#include <memory>
#include "../Core/Game.h"

class DeviceResources;
class InputDevice;

class CameraTestLab : public Game
{
public:
    CameraTestLab(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input);
};