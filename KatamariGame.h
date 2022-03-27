#pragma once
#include <memory>
#include <string>
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
    Actor* CreateSceneActor(std::shared_ptr<RenderData> renderData);
    Actor* CreateMeshActor(std::string meshPath, std::wstring texturePath, std::shared_ptr<RenderData> renderData);
    CameraComponent* CreateCamera(std::shared_ptr<InputDevice> input);
};