#include "Renderer.h"

#include "Camera.h"
#include "DefaultRenderPass.h"
#include "Material.h"
#include "SceneActor.h"
#include "WindowApplication.h"
#include "RenderPass.h"
#include "ShadowMapPass.h"

Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
{
    device_resources = deviceResources;
    main_ = new DefaultRenderPass(deviceResources);
}

void Renderer::CreateDeviceDependentResources()
{
    CreateRasterizerState();
}

void Renderer::AddShadowMapPass(CameraComponent* camera, LightComponent* light)
{
    additional_stages.push_back(new ShadowMapPass(device_resources, camera, light));
}

void Renderer::PassSceneActors(std::vector<SceneActor*>* actors)
{
    sceneActors = actors;
}

void Renderer::Render() const
{
    for (const auto pass : additional_stages)
        pass->Render(*sceneActors);

    main_->Render(*sceneActors);
}

void Renderer::CreateRasterizerState()
{
    ID3D11Device* device = device_resources->GetDevice();
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    CD3D11_RASTERIZER_DESC rastDesc = {};
    rastDesc.CullMode = D3D11_CULL_BACK;
    rastDesc.FillMode = D3D11_FILL_SOLID;

    ID3D11RasterizerState* rastState;
    HRESULT result = device->CreateRasterizerState(&rastDesc, &rastState);

    context->RSSetState(rastState);
}
