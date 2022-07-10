#pragma once
#include "MeshRenderData.h"

class LightRenderData : public MeshRenderData
{
public:
    LightRenderData(ID3D11Device* device, Material* material, Mesh* mesh, DirectX::SimpleMath::Vector3 color) :
        MeshRenderData(device, material, mesh, nullptr), color_(color) {}

    DirectX::SimpleMath::Vector3 GetColor() const { return color_; }

private:
    DirectX::SimpleMath::Vector3 color_;
};
