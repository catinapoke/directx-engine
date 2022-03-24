#include "KatamariGame.h"

#include "DeviceResources.h"
#include "InputDevice/InputDevice.h"

#include "Basic3DMaterial.h"
#include "LineStripMaterial.h"

#include "BoxRenderData.h"
#include "PlaneRenderData.h"

#include "TransformComponent.h"
#include "Camera.h"
#include "TransformController.h"

KatamariGame::KatamariGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input)
{
    ID3D11Device* device = deviceResources->GetDevice();

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    LineStripMaterial* debug_material = new LineStripMaterial(deviceResources);

    std::shared_ptr<RenderData> boxRenderData = std::make_shared<BoxRenderData>(device, material);
    std::shared_ptr<PlaneRenderData> planeRenderData = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(10, 10), 2.5f);
    // Load bunch of models

    CameraComponent* camera = CreateCamera(input);

    material->SetCamera(camera);
    debug_material->SetCamera(camera);

    CreateBox(boxRenderData);

    // CreatePickableActors
}

Actor* KatamariGame::CreateBox(std::shared_ptr<RenderData> boxRenderData)
{
    Actor* box = new Actor();
    box->AddComponent<TransformComponent>();

    actors.push_back(box);
    sceneActors.push_back(new SceneActor(box, boxRenderData));

    return box;
}

CameraComponent* KatamariGame::CreateCamera(std::shared_ptr<InputDevice> input)
{
    Actor* camera = new Actor();
    actors.push_back(camera);

    camera->AddComponent(new TransformComponent(Vector3(0, 2, 0)));
    camera->AddComponent(new TransformController(input));
    CameraComponent* component = camera->AddComponent<CameraComponent>();
    
    return component;
}
