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
    std::shared_ptr<PlaneRenderData> planeRenderData = std::make_shared<PlaneRenderData>(device, debug_material, Vector2(4,4), 1.f);

    Actor* sun = new Actor();
    TransformComponent* sun_t = new TransformComponent(sun);
    sun->AddComponent(sun_t);

    Actor* planet_1 = new Actor();
    Actor* planet_2 = new Actor();
    Actor* planet_3 = new Actor();
    Actor* planet_4 = new Actor();

    planet_1->AddComponent(new TransformComponent(planet_1, Vector3(-5, 0, 5), Vector3(), Vector3(1, 1, 1), sun_t));
    planet_2->AddComponent(new TransformComponent(planet_2, Vector3(5, 0, 5), Vector3(), Vector3(1, 1, 1), sun_t));
    planet_3->AddComponent(new TransformComponent(planet_3, Vector3(-5, 0, -5), Vector3(), Vector3(1, 1, 1), sun_t));
    planet_4->AddComponent(new TransformComponent(planet_4, Vector3(5, 0, -5), Vector3(), Vector3(1, 1, 1), sun_t));

    planet_1->AddComponent(new OrbitRotator(planet_1));
    planet_2->AddComponent(new OrbitRotator(planet_2));
    planet_3->AddComponent(new OrbitRotator(planet_3));
    planet_4->AddComponent(new OrbitRotator(planet_4));

    Actor* moon_1 = new Actor();
    Actor* moon_2 = new Actor();

    TransformComponent* moon_t_1 = new TransformComponent(
        moon_1,
        Vector3(0, 2, 0), Vector3(), Vector3(1, 1, 1),
        planet_1->GetComponent<TransformComponent>());

    TransformComponent* moon_t_2 = new TransformComponent(
        moon_2,
        Vector3(0, -2, 0), Vector3(), Vector3(1, 1, 1),
        planet_1->GetComponent<TransformComponent>());

    moon_1->AddComponent(moon_t_1);
    moon_2->AddComponent(moon_t_2);
    moon_1->AddComponent(new OrbitRotator(moon_1));
    moon_2->AddComponent(new OrbitRotator(moon_2));

    Actor* plane = new Actor();
    plane->AddComponent(new TransformComponent(plane));

    // Camera
    Actor* camera = new Actor();
    camera->AddComponent(new TransformComponent(camera, Vector3(0, 2, 0)));
    camera->AddComponent(new CameraComponent(camera));
    //camera->AddComponent(new RotateComponent(camera));
    camera->AddComponent(new TransformController(camera, input));

    // actors.push_back(camera);

    material->SetCamera(camera->GetComponent<CameraComponent>());
    debug_material->SetCamera(camera->GetComponent<CameraComponent>());

    actors = { sun,  planet_1,planet_2,planet_3, planet_4, moon_1, moon_2, camera, plane };
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