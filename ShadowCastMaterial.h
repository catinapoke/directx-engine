#pragma once
#include "Basic3DMaterial.h"
#include "LightComponent.h"

class ShadowCastMaterial : public Basic3DMaterial
{
public:
    ShadowCastMaterial(std::shared_ptr<DeviceResources> resources, CameraComponent* camera, LightComponent* light, std::wstring shader = L"Shaders/shader_shadow_map.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTextureNormal)
        :Basic3DMaterial(resources, shader, scheme), light_(light)
    {
        SetCamera(camera);
    }

protected:
    void SetProjectionViewMatrix() override
    {
        Matrix matrix = light_->GetProjectionViewMatrix().Transpose();
        MapBuffer(camera_buffer.Get(), &matrix, sizeof(Matrix));
    }

private:
    LightComponent* light_;
};
