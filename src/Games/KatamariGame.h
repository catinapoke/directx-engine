#pragma once
#include <DirectXMath.h>
#include <memory>
#include <string>
#include "../Core/Game.h"

class LightComponent;
class DeviceResources;
class InputDevice;
class RenderData;
class CameraComponent;
struct ID3D11Device;
class MeshMaterial;

class KatamariGame : public Game
{
public:
    KatamariGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input, std::shared_ptr<Renderer> renderer);

private:
    Actor* CreateSceneActor(std::shared_ptr<RenderData> renderData);
    Actor* CreateMeshActor(ID3D11Device* device, const std::string& mesh_path, const std::wstring& texture_path, MeshMaterial* material);
    Actor* CreatePickableActor(std::shared_ptr<RenderData> renderData, float radius, DirectX::XMFLOAT3 position);
    CameraComponent* CreateCamera(std::shared_ptr<InputDevice> input);
    LightComponent* CreateLight(DirectX::XMFLOAT3 position = { 0,0,0 }, 
        DirectX::XMFLOAT3 rotation = { 0,0,0 },
        DirectX::XMFLOAT4 color = { 1,1,1, 1 });
};