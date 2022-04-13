#include "Renderer.h"
#include "ConstantBuffers.h"
#include "Material.h"
#include "SceneActor.h"
#include "WindowApplication.h"

Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
{
    m_deviceResources = deviceResources;
}

void Renderer::CreateDeviceDependentResources()
{
    CreateViewAndPerspective();
}

void Renderer::PassSceneActors(std::vector<SceneActor*>* actors)
{
    sceneActors = actors;
}

void Renderer::Render()
{
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();
    ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargetView();
    ID3D11DepthStencilView* depthView = m_deviceResources->GetDepthStencilView();

    float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    context->ClearRenderTargetView(renderTarget, color);
    context->ClearDepthStencilView(depthView, D3D11_CLEAR_DEPTH, 1, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthView);

    UINT strides[] = { 32 };
    UINT offsets[] = { 0 };

    Material* currentMaterial = (*sceneActors)[0]->GetRenderData()->GetMaterial();
    currentMaterial->PrepareRender();

    for (SceneActor* item : *sceneActors)
    {
        std::shared_ptr<RenderData> renderData = item->GetRenderData();
        Material* item_material = renderData->GetMaterial();
        if (item_material != currentMaterial)
        {
            currentMaterial = item_material;
            currentMaterial->PrepareRender();
        }

        currentMaterial->PrepareObjectData(item);

        renderData->SetBuffers(context);

        // context->IASetIndexBuffer(renderData->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
        // context->IASetVertexBuffers(0, 1, renderData->GetVertexBufferAddress(), strides, offsets);
        context->DrawIndexed(renderData->GetIndicesCount(), 0, 0);
    }

    context->OMSetRenderTargets(0, nullptr, nullptr);
}

void Renderer::CreateViewAndPerspective()
{
    ID3D11Device* device = m_deviceResources->GetDevice();
    ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();

    CD3D11_RASTERIZER_DESC rastDesc = {};
    rastDesc.CullMode = D3D11_CULL_BACK;//
    rastDesc.FillMode = D3D11_FILL_SOLID;

    ID3D11RasterizerState* rastState;
    HRESULT result = device->CreateRasterizerState(&rastDesc, &rastState);

    context->RSSetState(rastState);

    /*DirectX::XMFLOAT2 window_size = WindowApplication::GetInstance()->GetWindowSize();

    D3D11_VIEWPORT viewport = {};
    viewport.Width =  window_size.x;
    viewport.Height = window_size.y;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);*/
}
