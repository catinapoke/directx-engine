#pragma once
#include "../Core/Material.h"
#include "../InputDevice/SimpleMath.h"
class CameraComponent;
class GeometryBuffer;

class DeferredMeshMaterial :public Material
{
public:
    DeferredMeshMaterial(std::shared_ptr<DeviceResources> resources,
        std::wstring shader = L"Shaders/shader_deferred_mesh.hlsl", //shader_mesh_light
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
        :Material(resources, shader, scheme)
    {
        CreateShader();
        DeferredMeshMaterial::CreateBuffers();
    };

    HRESULT CreateBuffers() override;
    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;

    void SetCamera(CameraComponent* camera);

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> transform_buffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> material_buffer;

    CameraComponent* camera_ = nullptr;

    DirectX::SimpleMath::Matrix transform_data[3];
};