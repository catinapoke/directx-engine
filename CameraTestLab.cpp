#include "CameraTestLab.h"
#include "DeviceResources.h"
#include "InputDevice/InputDevice.h"

#include "BoxRenderData.h"
#include "TransformComponent.h"
#include "SceneActor.h"
#include "Camera.h"
#include "Basic3DMaterial.h"


CameraTestLab::CameraTestLab(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input)
{
    ID3D11Device* device = deviceResources->GetDevice();

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    std::shared_ptr<RenderData> boxRenderData = std::make_shared<BoxRenderData>(device, material);
    
    actors = { new Actor(), new Actor(), new Actor() };
    actors[0]->AddComponent(new TransformComponent(actors[0], Vector3(-100, 0, 0)));
    actors[1]->AddComponent(new TransformComponent(actors[1], Vector3(0, -75, 0)));
    
    // Camera
    actors[2]->AddComponent(new TransformComponent(actors[2]));
    actors[2]->AddComponent(new CameraComponent(actors[2]));

    sceneActors = {
        new SceneActor(actors[0], boxRenderData),
        new SceneActor(actors[1], boxRenderData)
    };

    material->SetCamera(actors[2]->GetComponent<CameraComponent>());
}