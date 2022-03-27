#include "KatamariGame.h"
#include <DirectXTex.h>

#include "DeviceResources.h"
#include "MeshLoader.h"
#include "Utils\TextureLoader.h"
#include "InputDevice/InputDevice.h"

#include "Basic3DMaterial.h"
#include "LineStripMaterial.h"
#include "MeshMaterial.h"

#include "BoxRenderData.h"
#include "PlaneRenderData.h"
#include "MeshRenderData.h"

#include "TransformComponent.h"
#include "Camera.h"
#include "TransformController.h"

KatamariGame::KatamariGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input)
{
    ID3D11Device* device = deviceResources->GetDevice();

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    LineStripMaterial* debug_material = new LineStripMaterial(deviceResources);
    MeshMaterial* mesh_material = new MeshMaterial(deviceResources);

    std::shared_ptr<RenderData> boxRenderData = std::make_shared<BoxRenderData>(device, material);
    std::shared_ptr<RenderData> planeRenderData = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(10, 10), 2.5f);
    std::shared_ptr<RenderData> meshRenderData = std::make_shared<MeshRenderData>(device, mesh_material);
    // Load bunch of models

    CameraComponent* camera = CreateCamera(input);

    material->SetCamera(camera);
    debug_material->SetCamera(camera);

    CreateSceneActor(boxRenderData);

    // CreatePickableActors
}

Actor* KatamariGame::CreateSceneActor(std::shared_ptr<RenderData> renderData)
{
    Actor* actor = new Actor();
    actor->AddComponent<TransformComponent>();

    actors.push_back(actor);
    sceneActors.push_back(new SceneActor(actor, renderData));

    return actor;
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

Actor* KatamariGame::CreateMeshActor(std::string meshPath, 
    std::wstring texturePath, std::shared_ptr<RenderData> renderData)
{
    Mesh* mesh = MeshLoader::LoadFirst(meshPath);
    DirectX::ScratchImage* image;
    TextureLoader::LoadWic(texturePath.c_str(), image);
}