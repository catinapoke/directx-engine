#pragma once
#include "CommonRenderData.h"

class SphereRenderData :public CommonRenderData
{
public:
    SphereRenderData(Material* material) :CommonRenderData(material) {};
    SphereRenderData(ID3D11Device* device, Material* material);
};