#pragma once
#include "MeshRenderData.h"

class AmbientRenderData : public MeshRenderData
{
public:
    AmbientRenderData(ID3D11Device* device, Material* material, Mesh* mesh,
        DirectX::SimpleMath::Vector3 color, float strength) :
        MeshRenderData(device, material, mesh, nullptr), color_(color), strength_( strength) {}

    DirectX::SimpleMath::Vector3 GetColor() const { return color_; }\
    float GetStrength() const { return strength_; }

private:
    DirectX::SimpleMath::Vector3 color_;
    float strength_;
};
