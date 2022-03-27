#pragma once

#include <wrl.h>
#include "CommonRenderData.h"
class BoxRenderData :public CommonRenderData
{
public:
    BoxRenderData(Material* material): CommonRenderData(material) {};
    BoxRenderData(ID3D11Device* device, Material* material);
};