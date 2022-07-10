#pragma once
#include "CommonRenderData.h"
#include "../InputDevice/SimpleMath.h"

class Material;
typedef DirectX::SimpleMath::Vector2 Vector2;

class PlaneRenderData : public CommonRenderData
{
public:
    PlaneRenderData(Material* material): CommonRenderData(material) {};
    PlaneRenderData(ID3D11Device* device, Material* material, Vector2 square_count, float side_length);
};