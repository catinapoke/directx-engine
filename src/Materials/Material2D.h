#pragma once
#include "../Core/Material.h"
#include "../Core/ConstantBuffers.h"

class Material2D : public Material
{
public:
    Material2D(std::shared_ptr<DeviceResources> resources, std::wstring shader)
        :Material(resources, shader) {};

    HRESULT CreateInputLayout(ID3DBlob* compiledVertexBlob) override;
    HRESULT CreateBuffers() override;
    void PrepareRender() override;
    void PrepareObjectData(SceneActor* actor) override;

private:
    void SetPosition(PositionBuffer position_data);
    void SetDisplayAspects(DisplayBuffer display_data);    

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> positionBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> displayBuffer;
};