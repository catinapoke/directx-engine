#pragma once
#include "RenderPass.h"

class CameraComponent;
class ShadowMap;
class LightComponent;
class ShadowCastMaterial;

class ShadowMapPass:public RenderPass
{
public:
    ShadowMapPass(std::shared_ptr<DeviceResources> resources, CameraComponent* camera, LightComponent* light, int shadow_map_width = 2048, int shadow_map_height = 2048);
    ~ShadowMapPass() override;
    void Render(std::vector<SceneActor*>& actors) override;

protected:
    ShadowCastMaterial* shadow_map_material;
    ShadowMap* shadow_map;
};
