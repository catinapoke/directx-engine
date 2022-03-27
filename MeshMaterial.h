#pragma once
#include "Basic3DMaterial.h"
#include "Sampler.h"

class MeshMaterial : public Basic3DMaterial
{
public:
    MeshMaterial(std::shared_ptr<DeviceResources> resources, std::wstring shader = L"Shaders/shader_3d.hlsl")
        : Basic3DMaterial(resources, shader)
    {
        sampler = new Sampler(resources->GetDevice(), resources->GetDeviceContext());
    }

    HRESULT CreateInputLayout(ID3DBlob* compiledVertexBlob) override;
    void PrepareRender() override;

private:
    Sampler* sampler;
};