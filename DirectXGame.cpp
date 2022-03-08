#pragma once
#include <windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <iostream>
#include <memory>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>

#include "WindowApplication.h"
#include "DeviceResources.h"
#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

int main(int argc, char** argv)
{
    std::shared_ptr<WindowApplication> application = std::shared_ptr<WindowApplication>(new WindowApplication());
    std::shared_ptr<DeviceResources> resources = std::shared_ptr<DeviceResources>(new DeviceResources());
    std::shared_ptr<Renderer> renderer = std::shared_ptr<Renderer>(new Renderer(resources));

    application->CreateDesktopWindow();
    resources->InitializeDeviceResources(application->GetHandle());
    renderer->CreateDeviceDependentResources();

    application->Run(resources, renderer);
}
