#include "KatamariGame.h"
#include <vector>

#include "../Core/DeviceResources.h"
#include "../Core/Renderer.h"

#include "../Utils/MeshLoader.h"
#include "../InputDevice/InputDevice.h"

#include "../Materials/Basic3DMaterial.h"
#include "../Materials/LineStripMaterial.h"
#include "../Materials/MeshMaterial.h"
#include "../Materials/DebugTextureMaterial.h"
#include "../Materials/PhongMeshMaterial.h"

#include "../RenderData/BoxRenderData.h"
#include "../RenderData/PlaneRenderData.h"
#include "../RenderData/MeshRenderData.h"
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

Mesh* CreateBoxMesh();

KatamariGame::KatamariGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input, std::shared_ptr<Renderer> renderer)
{
    ID3D11Device* device = deviceResources->GetDevice();

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    LineStripMaterial* debug_material = new LineStripMaterial(deviceResources);
    PhongMeshMaterial* mesh_material = new PhongMeshMaterial(deviceResources);
    DebugTextureMaterial* debug_texture_material = new DebugTextureMaterial(deviceResources);

    // Load models and textures
    Texture* texture = new Texture(device, L"Textures/clown_double.png");
    Mesh* simple_mesh = MeshLoader::LoadFirst("Meshes/sphere.obj");

    Texture* money_texture = new Texture(device, L"Textures/money.png");
    Mesh* money_mesh = MeshLoader::LoadFirst("Meshes/money.obj");

    Texture* gas_texture = new Texture(device, L"Textures/gas_bottle.png");
    Mesh* gas_mesh = MeshLoader::LoadFirst("Meshes/gas_bottle.obj");

    Texture* plane_texture = new Texture(device, L"Textures/white.png");
    Mesh* plane_mesh = MeshLoader::LoadFirst("Meshes/h_plane.obj");

    // Link render data
    std::shared_ptr<RenderData> box_render_data = std::make_shared<BoxRenderData>(device, material);
    std::shared_ptr<RenderData> plane_render_data = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(10, 10), 2.5f);
    std::shared_ptr<RenderData> mesh_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, simple_mesh, texture, {0.05f,0.2f,0.1f,0}));

    std::shared_ptr<RenderData> money_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, money_mesh, money_texture, { 0.05f,0.1f,0.3f,0 }));
    std::shared_ptr<RenderData> gas_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, gas_mesh, gas_texture, { 0.05f,0.3f,0.1f,0 }));
    std::shared_ptr<RenderData> mesh_plane_render_data = std::shared_ptr<PhongRenderData>(new PhongRenderData(device, mesh_material, plane_mesh, plane_texture, { 0.05f,0.3f,0.1f,0 }));
    std::shared_ptr<RenderData> debug_texture_render_data = std::make_shared<MeshRenderData>(device, debug_texture_material, money_mesh, money_texture);

    // Init actors
    LightComponent* light = CreateLight(
        {0,3,3},
        {0, -45, 0}
    );
    CameraComponent* camera = CreateCamera(input);
    camera->GetActor()->GetComponent<TransformComponent>()->SetLocalPosition(Vector3(0, 2, 3));

    material->SetCamera(camera);
    debug_material->SetCamera(camera);
    mesh_material->SetCamera(camera);
    mesh_material->SetLight(light);

    CreateSceneActor(plane_render_data);
    Actor* mr_clown = CreateSceneActor(mesh_render_data);
    mr_clown->AddComponent(new KatamariSphereController(input, camera));
    mr_clown->AddComponent(new SphereCollider(0.5f));
    mr_clown->AddComponent<KatamariPicker>();

    CreatePickableActor(money_render_data, 0.25f, { 1,0,0 });
    CreatePickableActor(money_render_data, 0.25f, { 1,0,1 })
        ->GetComponent<TransformComponent>()->SetLocalScale({ 0.5f,0.5f, 0.5f });
    CreatePickableActor(gas_render_data, 0.6f, { 1,0,0 })
        ->GetComponent<TransformComponent>()->SetLocalScale({ 0.25f,0.25f, 0.25f });
    //CreatePickableActor(box_render_data, 0.4f, { 0, 0, 4 });
    TransformComponent* plane_transform = CreateSceneActor(mesh_plane_render_data)
        ->GetComponent<TransformComponent>();
    plane_transform->SetLocalScale({ 5.25f,5.25f, 5.25f });
    plane_transform->SetLocalPosition({ 0.f,-0.75f, 0.f });

    //CreateSceneActor(debug_texture_render_data)
    //    ->GetComponent<TransformComponent>()->SetLocalRotation({ 0, -90,0 });

    camera->GetActor()->GetComponent<TransformComponent>()->SetParent(mr_clown->GetComponent<TransformComponent>());

    renderer->AddShadowMapPass(camera, light);
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

    camera->AddComponent(new OrbitTransform());
    camera->AddComponent(new OrbitTransformController(input));
    CameraComponent* component = camera->AddComponent<CameraComponent>();

    return component;
}

LightComponent* KatamariGame::CreateLight(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT4 color)
{
    Actor* actor = new Actor();
    actors.push_back(actor);

    TransformComponent* transform = actor->AddComponent<TransformComponent>();
    transform->SetLocalPosition(position);
    transform->SetLocalRotation(rotation);

    LightComponent* light = new LightComponent(color);
    actor->AddComponent(light);

    return light;
}

Actor* KatamariGame::CreateMeshActor(ID3D11Device* device, const std::string& mesh_path,
                                     const std::wstring& texture_path, MeshMaterial* material)
{
    Texture* texture = new Texture(device, texture_path.c_str());
    Mesh* mesh = MeshLoader::LoadFirst(mesh_path);
    std::shared_ptr<RenderData> mesh_render_data = std::make_shared<MeshRenderData>(device, material, mesh, texture);
    return CreateSceneActor(mesh_render_data);
}

Actor* KatamariGame::CreatePickableActor(std::shared_ptr<RenderData> renderData, float radius, DirectX::XMFLOAT3 position)
{
    Actor* actor = CreateSceneActor(renderData);
    actor->AddComponent(new SphereCollider(radius));
    actor->GetComponent<TransformComponent>()->SetLocalPosition(position);
    return actor;
}

Mesh* CreateBoxMesh()
{
    //Vertex buffer
    const DirectX::XMFLOAT4 points[8] =
    {
        DirectX::XMFLOAT4(-0.5f, 0.5f, -0.5f, 1.0f),  // +Y (top face)
        DirectX::XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f),
        DirectX::XMFLOAT4(0.5f, 0.5f,  0.5f, 1.0f),
        DirectX::XMFLOAT4(-0.5f, 0.5f,  0.5f, 1.0f),

        DirectX::XMFLOAT4(-0.5f, -0.5f,  0.5f, 1.0f),  // -Y (bottom face)
        DirectX::XMFLOAT4(0.5f, -0.5f,  0.5f, 1.0f),
        DirectX::XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f),
        DirectX::XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f),

    };

    // Index buffer
    const int indices[36] = { 0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    3, 2, 5,
    3, 5, 4,

    2, 1, 6,
    2, 6, 5,

    1, 7, 6,
    1, 0, 7,

    0, 3, 4,
    0, 4, 7 };

    std::vector<VertexData> vertices = {};
    for (int i = 0; i < std::size(points); i++)
    {
        DirectX::SimpleMath::Vector3 pos = { points[i].x, points[i].y, points[i].z };
        vertices.push_back(VertexData(pos));
    }

    std::vector<int> indices_arr = {};
    for (int i = 0; i < std::size(indices); i++)
    {
        indices_arr.push_back(indices[i]);
    }

    return new Mesh(vertices, indices_arr);
}
