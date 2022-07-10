#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

#include "../Core/Game.h"

class DeferredDirectionalMaterial;
class DeferredPointMaterial;
class DeferredAmbientMaterial;
class LightComponent;
class CameraComponent;
class MeshMaterial;
class RenderData;

class DeferredLightLab : public Game
{
public:
    DeferredLightLab(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input, std::shared_ptr<Renderer> renderer);

private:
    Actor* CreateSceneActor(std::shared_ptr<RenderData> renderData);
    Actor* CreateMeshActor(ID3D11Device* device, const std::string& mesh_path, const std::wstring& texture_path, MeshMaterial* material);
    Actor* CreatePickableActor(std::shared_ptr<RenderData> renderData, float radius, DirectX::XMFLOAT3 position);
    CameraComponent* CreateCamera(std::shared_ptr<InputDevice> input);

    LightComponent* CreateAmbientLight(ID3D11Device* device, DeferredAmbientMaterial* material, float strength = 0.01f, DirectX::XMFLOAT3 color = { 1,1,1 });
    LightComponent* CreatePointLight(ID3D11Device* device, DeferredPointMaterial* material, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color = { 1,1,1 });
    LightComponent* CreateDirectionalLight(ID3D11Device* device, DeferredDirectionalMaterial* material, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 color = { 1,1,1 });

    LightComponent* CreateLight(std::shared_ptr<RenderData> renderData, 
        DirectX::XMFLOAT3 position = { 0,0,0 },
        DirectX::XMFLOAT3 rotation = { 0,0,0 },
        DirectX::XMFLOAT4 color = { 1,1,1, 1 });
};
