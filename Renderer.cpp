#include "Renderer.h"

#include "Camera.h"
#include "DefaultRenderPass.h"
#include "Material.h"
#include "SceneActor.h"
#include "WindowApplication.h"
#include "RenderPass.h"
#include "ShadowMapPass.h"

Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
{
    device_resources = deviceResources;
    main_ = new DefaultRenderPass(deviceResources);
}

void Renderer::AddShadowMapPass(CameraComponent* camera, LightComponent* light)
{
    additional_stages.push_back(new ShadowMapPass(device_resources, camera, light));
}

void Renderer::ChangeMain(RenderPass* pass)
{
    main_ = pass;
}

void Renderer::PassSceneActors(std::vector<SceneActor*>* actors)
{
    sceneActors = actors;
}

void Renderer::Render() const
{
    for (const auto pass : additional_stages)
        pass->Render(*sceneActors);

    main_->Render(*sceneActors);
}
