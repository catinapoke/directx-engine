#pragma once
#include "Basic3DMaterial.h"
#include "Sampler.h"

class MeshMaterial : public Basic3DMaterial
{
public:
    MeshMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_mesh.hlsl", 
        InputScheme scheme = InputLayoutSchemes::PositionTexture)
        : Basic3DMaterial(resources, shader, scheme)
    {
        sampler = new Sampler(resources->GetDevice(), resources->GetDeviceContext());
    }

    void PrepareRender() override;

protected:
    Sampler* sampler;
};