#pragma once
#include <memory>
#include <vector>

#include "DeviceResources.h"
#include "../Components/LightComponent.h"

class CameraComponent;
class SceneActor;
class RenderPass;

class Renderer
{
public:
    Renderer(std::shared_ptr<DeviceResources> deviceResources);
    ~Renderer() {};

    void Render() const;

    void AddShadowMapPass(CameraComponent* camera, LightComponent* light);
    void ChangeMain(RenderPass* pass);
    void PassSceneActors(std::vector<SceneActor*>* actors);

private:
    std::vector<SceneActor*>* sceneActors;
    std::shared_ptr<DeviceResources> device_resources;

    RenderPass* main_;
    std::vector<RenderPass*> additional_stages;
};