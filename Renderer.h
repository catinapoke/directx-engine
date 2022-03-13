#pragma once
#include <memory>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <iostream>
#include <chrono>
#include <vector>

#include "DeviceResources.h"
#include "ConstantBuffers.h"

class SceneActor;

class Renderer
{
public:
    Renderer(std::shared_ptr<DeviceResources> deviceResources);
    ~Renderer() {};

    void CreateDeviceDependentResources();
    void PassSceneActors(std::vector<SceneActor*>* actors);
    void CreateWindowSizeDependentResources();
    void Render();

private:
    void CreateViewAndPerspective();

private:
    std::vector<SceneActor*>* sceneActors;
    std::shared_ptr<DeviceResources> m_deviceResources;
};