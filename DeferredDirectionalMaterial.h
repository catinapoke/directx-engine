#pragma once
#include "DeferredLightMaterial.h"
#include "InputDevice/SimpleMath.h"

class CameraComponent;

class DeferredDirectionalMaterial : public DeferredLightMaterial
{
public:
    DeferredDirectionalMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_deferred_light_directional.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
        :DeferredLightMaterial(resources, shader, scheme)
    {
        CreateShader();
        DeferredDirectionalMaterial::CreateBuffers();
    };

public:
    void SetCamera(CameraComponent* camera) override;

    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;
protected:
    HRESULT CreateBuffers() override;

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> light_buffer;
    CameraComponent* camera_ = nullptr;
};
