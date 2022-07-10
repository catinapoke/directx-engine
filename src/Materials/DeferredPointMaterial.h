#pragma once
#include "DeferredLightMaterial.h"
#include "../InputDevice/SimpleMath.h"

class DeferredPointMaterial : public DeferredLightMaterial
{
public:
    DeferredPointMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_deferred_light_point.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
        :DeferredLightMaterial(resources, shader, scheme)
    {
        CreateShader();
        DeferredPointMaterial::CreateBuffers();
    };

public:
    void SetCamera(CameraComponent* camera) override;

    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;
protected:
    HRESULT CreateBuffers() override;

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> transform_buffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> light_buffer;

    CameraComponent* camera_ = nullptr;
    DirectX::SimpleMath::Matrix transform_data[2];
};
