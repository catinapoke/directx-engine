#include "KatamariGame.h"
#include <vector>

#include "DeviceResources.h"
#include "MeshLoader.h"
#include "InputDevice/InputDevice.h"

#include "Basic3DMaterial.h"
#include "LineStripMaterial.h"
#include "MeshMaterial.h"

#include "BoxRenderData.h"
#include "PlaneRenderData.h"
#include "MeshRenderData.h"

#include "TransformComponent.h"
#include "Camera.h"
#include "KatamariSphereController.h"
#include "OrbitTransform.h"
#include "OrbitTransformController.h"
#include "TransformController.h"

Mesh* CreateBoxMesh();

KatamariGame::KatamariGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input)
{
    ID3D11Device* device = deviceResources->GetDevice();

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    LineStripMaterial* debug_material = new LineStripMaterial(deviceResources);
    MeshMaterial* mesh_material = new MeshMaterial(deviceResources);

    Texture* texture = new Texture(device, L"Textures/clown_double.png");
    Mesh* simple_mesh = MeshLoader::LoadFirst("Meshes/sphere.obj");
    //Mesh* simple_mesh = MeshLoader::LoadFirst("Meshes/box_rotate.obj");
    //Mesh* simple_mesh = CreateBoxMesh();// MeshLoader::LoadFirst("Meshes/box_rotate.obj");

    std::shared_ptr<RenderData> box_render_data = std::make_shared<BoxRenderData>(device, material);
    std::shared_ptr<RenderData> plane_render_data = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(10, 10), 2.5f);
    std::shared_ptr<RenderData> mesh_render_data = std::make_shared<MeshRenderData>(device, mesh_material, simple_mesh, texture);
    // Load bunch of models

    CameraComponent* camera = CreateCamera(input);
    camera->GetActor()->GetComponent<TransformComponent>()->SetLocalPosition(Vector3(0, 2, 3));

    material->SetCamera(camera);
    debug_material->SetCamera(camera);
    mesh_material->SetCamera(camera);

    Actor* box = CreateSceneActor(box_render_data);
    CreateSceneActor(plane_render_data);
    Actor* mr_clown = CreateSceneActor(mesh_render_data);
    mr_clown->AddComponent(new KatamariSphereController(input, camera));

    box->GetComponent<TransformComponent>()->SetLocalPosition(Vector3(0, 3, 0));

    camera->GetActor()->GetComponent<TransformComponent>()->SetParent(mr_clown->GetComponent<TransformComponent>());
    //camera->GetActor()->GetComponent<TransformComponent>()->SetParent(nullptr);
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

    camera->AddComponent(new OrbitTransform());
    camera->AddComponent(new OrbitTransformController(input));
    CameraComponent* component = camera->AddComponent<CameraComponent>();

    return component;
}

Actor* KatamariGame::CreateMeshActor(ID3D11Device* device, const std::string& mesh_path,
    const std::wstring& texture_path, MeshMaterial* material)
{
    Texture* texture = new Texture(device, texture_path.c_str());
    Mesh* mesh = MeshLoader::LoadFirst(mesh_path);
    std::shared_ptr<RenderData> mesh_render_data = std::make_shared<MeshRenderData>(device, material, mesh, texture);
    return CreateSceneActor(mesh_render_data);
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