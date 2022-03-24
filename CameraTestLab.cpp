#include "CameraTestLab.h"
#include "DeviceResources.h"
#include "InputDevice/InputDevice.h"

#include "BoxRenderData.h"
#include "TransformComponent.h"
#include "SceneActor.h"
#include "Camera.h"
#include "Basic3DMaterial.h"
#include "RotateComponent.h"
#include "OrbitRotator.h"
#include "TransformController.h"
#include "SphereRenderData.h"
#include "LineStripMaterial.h"
#include "PlaneRenderData.h"

CameraTestLab::CameraTestLab(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input)
{
    ID3D11Device* device = deviceResources->GetDevice();

    Basic3DMaterial* material = new Basic3DMaterial(deviceResources);
    LineStripMaterial* debug_material = new LineStripMaterial(deviceResources);
    
    std::shared_ptr<RenderData> boxRenderData = std::make_shared<BoxRenderData>(device, material);
    std::shared_ptr<PlaneRenderData> planeRenderData = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(10,10), 2.5f);

    Actor* sun = new Actor();
    TransformComponent* sun_t = sun->AddComponent<TransformComponent>();

    Actor* planet_1 = new Actor();
    Actor* planet_2 = new Actor();
    Actor* planet_3 = new Actor();
    Actor* planet_4 = new Actor();

    planet_1->AddComponent(new TransformComponent(Vector3(-5, 0, 5), Vector3(), Vector3(1, 1, 1), sun_t));
    planet_2->AddComponent(new TransformComponent(Vector3(5, 0, 5), Vector3(), Vector3(1, 1, 1), sun_t));
    planet_3->AddComponent(new TransformComponent(Vector3(-5, 0, -5), Vector3(), Vector3(1, 1, 1), sun_t));
    planet_4->AddComponent(new TransformComponent(Vector3(5, 0, -5), Vector3(), Vector3(1, 1, 1), sun_t));

    planet_1->AddComponent<OrbitRotator>();
    planet_2->AddComponent<OrbitRotator>();
    planet_3->AddComponent<OrbitRotator>();
    planet_4->AddComponent<OrbitRotator>();

    Actor* moon_1 = new Actor();
    Actor* moon_2 = new Actor();

    TransformComponent* moon_t_1 = new TransformComponent(
        Vector3(0, 2, 0), Vector3(), Vector3(1, 1, 1),
        planet_1->GetComponent<TransformComponent>());

    TransformComponent* moon_t_2 = new TransformComponent(
        Vector3(0, -2, 0), Vector3(), Vector3(1, 1, 1),
        planet_1->GetComponent<TransformComponent>());

    moon_1->AddComponent(moon_t_1);
    moon_2->AddComponent(moon_t_2);
    moon_1->AddComponent<OrbitRotator>();
    moon_2->AddComponent<OrbitRotator>();

    Actor* plane = new Actor();
    plane->AddComponent<TransformComponent>();

    // Camera
    Actor* camera = new Actor();
    camera->AddComponent(new TransformComponent(Vector3(0, 2, 0)));
    camera->AddComponent<CameraComponent>();
    camera->AddComponent(new TransformController(input));

    material->SetCamera(camera->GetComponent<CameraComponent>());
    debug_material->SetCamera(camera->GetComponent<CameraComponent>());

    actors = { sun, planet_1,planet_2,planet_3, planet_4, moon_1, moon_2, camera, plane };
    sceneActors = {
        new SceneActor(sun, boxRenderData),
        new SceneActor(planet_1, boxRenderData),
        new SceneActor(planet_2, boxRenderData),
        new SceneActor(planet_3, boxRenderData),
        new SceneActor(planet_4, boxRenderData),
        new SceneActor(moon_1, boxRenderData),
        new SceneActor(moon_2, boxRenderData),
       new SceneActor(plane, planeRenderData)
    };
}