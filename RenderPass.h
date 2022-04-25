#pragma once
#include <vector>

#include "DeviceResources.h"
#include "SceneActor.h"

class RenderPass
{
public:
    RenderPass(std::shared_ptr<DeviceResources> resources) : device_resources(resources) {}
    virtual ~RenderPass() = default;

    virtual void Render(std::vector<SceneActor*>& actors) = 0;

protected:
    std::shared_ptr<DeviceResources> device_resources;
};
