#pragma once
#include "Material.h"

class DebugTextureMaterial : public Material
{
public:
    DebugTextureMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_texture_debug.hlsl",
        InputScheme scheme = InputLayoutSchemes::PositionTexture)
        :Material(resources, shader, scheme)
    {
        CreateShader();
    };

    HRESULT CreateBuffers() override;
    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;
};
