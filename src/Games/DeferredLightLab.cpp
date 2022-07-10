#include "DeferredLightLab.h"

#include <vector>

#include "../Core/DeviceResources.h"
#include "../Core/Renderer.h"

#include "../InputDevice/InputDevice.h"

#include "../Materials/Basic3DMaterial.h"
#include "../Materials/LineStripMaterial.h"
#include "../Materials/MeshMaterial.h"
#include "../Materials/DebugTextureMaterial.h"

#include "../Materials/DeferredAmbientMaterial.h"
#include "../Materials/DeferredDirectionalMaterial.h"
#include "../Materials/DeferredLightMaterial.h"
#include "../Materials/DeferredMeshMaterial.h"
#include "../Materials/DeferredPointMaterial.h"
#include "../Materials/PhongMeshMaterial.h"

#include "../RenderData/AmbientRenderData.h"
#include "../RenderData/BoxRenderData.h"
#include "../RenderData/PlaneRenderData.h"
#include "../RenderData/MeshRenderData.h"
#include "../RenderData/LightRenderData.h"
#include "../RenderData/PhongRenderData.h"

#include "../Components/TransformComponent.h"
#include "../Components/Camera.h"
#include "../Components/LightComponent.h"
#include "../Components/KatamariPicker.h"
#include "../Components/KatamariSphereController.h"
#include "../Components/OrbitTransform.h"
#include "../Components/OrbitTransformController.h"
#include "../Components/SphereCollider.h"
#include "../Components/TransformController.h"

#include "../RenderStages/DeferredRenderPass.h"

#include "../Utils/MeshLibrary.h"
#include "../Utils/MeshLoader.h"

DeferredLightLab::DeferredLightLab(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input, std::shared_ptr<Renderer> renderer)
{
    renderer->ChangeMain(new DeferredRenderPass(deviceResources));

    ID3D11Device* device = deviceResources->GetDevice();

    // Materials

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    LineStripMaterial* debug_material = new LineStripMaterial(deviceResources);
    DeferredMeshMaterial* mesh_material = new DeferredMeshMaterial(deviceResources);
    DebugTextureMaterial* debug_texture_material = new DebugTextureMaterial(deviceResources);

    DeferredPointMaterial* point_light_material = new DeferredPointMaterial(deviceResources);
    DeferredAmbientMaterial* ambient_light_material = new DeferredAmbientMaterial(deviceResources);
    DeferredDirectionalMaterial* directional_light_material = new DeferredDirectionalMaterial(deviceResources);

    // Load models and textures
    Texture* texture = new Texture(device, L"Textures/clown_double.png", true);
    Mesh* simple_mesh = MeshLoader::LoadFirst("Meshes/sphere.obj");

    Texture* money_texture = new Texture(device, L"Textures/money.png", true);
    Mesh* money_mesh = MeshLoader::LoadFirst("Meshes/money.obj");

    Texture* gas_texture = new Texture(device, L"Textures/gas_bottle.png", true);
    Mesh* gas_mesh = MeshLoader::LoadFirst("Meshes/gas_bottle.obj");

    Texture* plane_texture = new Texture(device, L"Textures/white.png", true);
    Mesh* plane_mesh = MeshLoader::LoadFirst("Meshes/h_plane.obj");

    // Link render data
    std::shared_ptr<RenderData> box_render_data = std::make_shared<BoxRenderData>(device, material);
    std::shared_ptr<RenderData> plane_render_data = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(10, 10), 2.5f);
    std::shared_ptr<RenderData> mesh_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, simple_mesh, texture, { 0.05f,0.2f,0.1f,0 }));

    std::shared_ptr<RenderData> money_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, money_mesh, money_texture, { 0.05f,0.1f,0.3f,0 }));
    std::shared_ptr<RenderData> gas_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, gas_mesh, gas_texture, { 0.05f,0.3f,0.1f,0 }));
    std::shared_ptr<RenderData> mesh_plane_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, plane_mesh, plane_texture, { 0.05f,0.3f,0.1f,0 }));
    std::shared_ptr<RenderData> debug_texture_render_data = std::make_shared<MeshRenderData>(device, debug_texture_material, money_mesh, money_texture);

    // Init actors
    LightComponent* ambient = CreateAmbientLight(device, ambient_light_material, 0.05);
    //LightComponent* directional = CreateDirectionalLight(device, directional_light_material, { 0, -45, 0 });
    LightComponent* point = CreatePointLight(device, point_light_material, { 0, 0, 5 });

    CameraComponent* camera = CreateCamera(input);
    camera->GetActor()->GetComponent<TransformComponent>()->SetLocalPosition(Vector3(0, 2, 3));

    material->SetCamera(camera);
    debug_material->SetCamera(camera);
    mesh_material->SetCamera(camera);
    point_light_material->SetCamera(camera);
    ambient_light_material->SetCamera(camera);
    directional_light_material->SetCamera(camera);

    CreateSceneActor(plane_render_data);
    Actor* mr_clown = CreateSceneActor(mesh_render_data);
    mr_clown->AddComponent(new KatamariSphereController(input, camera));
    mr_clown->AddComponent(new SphereCollider(0.5f));
    mr_clown->AddComponent<KatamariPicker>();

    CreatePickableActor(money_render_data, 0.25f, { 1,0,0 });
    CreatePickableActor(money_render_data, 0.25f, { 1,0,1 })
        ->GetComponent<TransformComponent>()->SetLocalScale({ 0.5f,0.5f, 0.5f });
    CreatePickableActor(gas_render_data, 0.6f, { 0,0,5 })
        ->GetComponent<TransformComponent>()->SetLocalScale({ 0.25f,0.25f, 0.25f });
   
    TransformComponent* plane_transform = CreateSceneActor(mesh_plane_render_data)
        ->GetComponent<TransformComponent>();
    plane_transform->SetLocalScale({ 5.25f,5.25f, 5.25f });
    plane_transform->SetLocalPosition({ 0.f,-0.75f, 0.f });

    camera->GetActor()->GetComponent<TransformComponent>()->SetParent(mr_clown->GetComponent<TransformComponent>());
}

Actor* DeferredLightLab::CreateSceneActor(std::shared_ptr<RenderData> renderData)
{
    Actor* actor = new Actor();
    actor->AddComponent<TransformComponent>();

    actors.push_back(actor);
    sceneActors.push_back(new SceneActor(actor, renderData));

    return actor;
}

CameraComponent* DeferredLightLab::CreateCamera(std::shared_ptr<InputDevice> input)
{
    Actor* camera = new Actor();
    actors.push_back(camera);

    camera->AddComponent(new OrbitTransform());
    camera->AddComponent(new OrbitTransformController(input));
    CameraComponent* component = camera->AddComponent<CameraComponent>();

    return component;
}

LightComponent* DeferredLightLab::CreateAmbientLight(ID3D11Device* device, DeferredAmbientMaterial* material, float strength, DirectX::XMFLOAT3 color)
{
    std::shared_ptr<RenderData> render_data = std::make_shared<AmbientRenderData>(
        device, material, MeshLibrary::GetScreenQuad().get(), color, strength);
    return CreateLight(render_data);
}

LightComponent* DeferredLightLab::CreatePointLight(ID3D11Device* device, DeferredPointMaterial* material, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color)
{
    std::shared_ptr<RenderData> render_data = std::make_shared<LightRenderData>(
        device, material, MeshLibrary::GetSphere().get(), color);
    LightComponent* light = CreateLight(render_data, pos);
    light->GetActor()->GetComponent<TransformComponent>()->SetLocalScale({ 10,10,10 });
    return light;
}

LightComponent* DeferredLightLab::CreateDirectionalLight(ID3D11Device* device, DeferredDirectionalMaterial* material, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 color)
{
    std::shared_ptr<RenderData> render_data = std::make_shared<LightRenderData>(
        device, material, MeshLibrary::GetScreenQuad().get(), color);
    return CreateLight(render_data, {0,0,0}, rotation);
}

LightComponent* DeferredLightLab::CreateLight(std::shared_ptr<RenderData> renderData, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT4 color)
{
    Actor* actor = new Actor();

    TransformComponent* transform = actor->AddComponent<TransformComponent>();
    transform->SetLocalPosition(position);
    transform->SetLocalRotation(rotation);

    LightComponent* light = new LightComponent(color);
    actor->AddComponent(light);

    actors.push_back(actor);
    sceneActors.push_back(new SceneActor(actor, renderData));

    return light;
}

Actor* DeferredLightLab::CreateMeshActor(ID3D11Device* device, const std::string& mesh_path,
    const std::wstring& texture_path, MeshMaterial* material)
{
    Texture* texture = new Texture(device, texture_path.c_str());
    Mesh* mesh = MeshLoader::LoadFirst(mesh_path);
    std::shared_ptr<RenderData> mesh_render_data = std::make_shared<MeshRenderData>(device, material, mesh, texture);
    return CreateSceneActor(mesh_render_data);
}

Actor* DeferredLightLab::CreatePickableActor(std::shared_ptr<RenderData> renderData, float radius, DirectX::XMFLOAT3 position)
{
    Actor* actor = CreateSceneActor(renderData);
    actor->AddComponent(new SphereCollider(radius));
    actor->GetComponent<TransformComponent>()->SetLocalPosition(position);
    return actor;
}