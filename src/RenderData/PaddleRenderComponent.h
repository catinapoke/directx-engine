#pragma once
#include <wrl.h>
#include "CommonRenderData.h"
class PaddleRenderComponent :public CommonRenderData
{
public:
    PaddleRenderComponent():CommonRenderData(nullptr) {};
    PaddleRenderComponent(ID3D11Device* device);
};