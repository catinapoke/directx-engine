#include "DefaultRenderPass.h"
#include "Material.h"

DefaultRenderPass::DefaultRenderPass(std::shared_ptr<DeviceResources> resources)
    :RenderPass(resources)
{
}

void DefaultRenderPass::Render(std::vector<SceneActor*>& actors)
{
    constexpr float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();
    ID3D11RenderTargetView* render_target = device_resources->GetRenderTargetView();
    ID3D11DepthStencilView* depth_view = device_resources->GetDepthStencilView();

    device_resources->SetViewport();
    context->OMSetRenderTargets(1, &render_target, depth_view);
    context->ClearRenderTargetView(render_target, color);
    context->ClearDepthStencilView(depth_view, D3D11_CLEAR_DEPTH, 1, 0);

    Material* currentMaterial = actors[0]->GetRenderData()->GetMaterial();
    currentMaterial->PrepareRender();

    for (SceneActor* item : actors)
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
        context->DrawIndexed(renderData->GetIndicesCount(), 0, 0);
    }

    context->OMSetRenderTargets(0, nullptr, nullptr);
}
