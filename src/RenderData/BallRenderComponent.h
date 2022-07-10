#pragma once
#include <wrl.h>
#include "CommonRenderData.h"
class BallRenderComponent :public CommonRenderData
{
public:
    BallRenderComponent() : CommonRenderData(nullptr) {};
    BallRenderComponent(ID3D11Device* device);
};