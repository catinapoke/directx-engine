#pragma once
#include <memory>

#include "WindowApplication.h"
#include "DeviceResources.h"
#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

int main(int argc, char** argv)
{
    std::shared_ptr<WindowApplication> application = std::make_shared<WindowApplication>();
    std::shared_ptr<DeviceResources> resources = std::make_shared<DeviceResources>();
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(resources);

    application->CreateDesktopWindow();
    resources->InitializeDeviceResources(application->GetHandle());

    application->Run(resources, renderer);
}
