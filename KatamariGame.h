#pragma once
#include <memory>
#include "Game.h"

class DeviceResources;
class InputDevice;
class RenderData;
class CameraComponent;

class KatamariGame : public Game
{
public:
    KatamariGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input);

private:
    Actor* CreateBox(std::shared_ptr<RenderData> boxRenderData);
    CameraComponent* CreateCamera(std::shared_ptr<InputDevice> input);
};