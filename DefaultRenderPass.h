#pragma once
#include "RenderPass.h"

class DefaultRenderPass :public RenderPass
{
public:
    DefaultRenderPass(std::shared_ptr<DeviceResources> resources);
    void Render(std::vector<SceneActor*>& actors) override;
};