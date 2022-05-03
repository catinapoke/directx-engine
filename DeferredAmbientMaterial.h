#pragma once
#include "DeferredLightMaterial.h"

class DeferredAmbientMaterial : public DeferredLightMaterial
{
public:
    DeferredAmbientMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_deferred_light_ambient.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
        :DeferredLightMaterial(resources, shader, scheme)
    {
        CreateShader();
        DeferredAmbientMaterial::CreateBuffers();
    };

public:
    void SetCamera(CameraComponent* camera) override {};

    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;
protected:
    HRESULT CreateBuffers() override;

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> light_buffer;
};
