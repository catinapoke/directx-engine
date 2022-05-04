#pragma once
#include "DeferredRenderPass.h"

#include <iostream>

#include "DeferredLightMaterial.h"
#include "GeometryBuffer.h"
#include "DeferredMeshMaterial.h"

DeferredRenderPass::DeferredRenderPass(std::shared_ptr<DeviceResources> resources) 
    : RenderPass(resources), geometry_buffer_(new GeometryBuffer(resources)), actors_buffer(8)
{
}

void DeferredRenderPass::Render(std::vector<SceneActor*>& actors)
{
    RenderObjects(actors);
    RenderLights(actors);
}

void DeferredRenderPass::RenderObjects(std::vector<SceneActor*>& actors)
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    FilterByMaterialInBuffer<DeferredMeshMaterial>(actors);

    device_resources->SetBlendNoneState();
    device_resources->SetDepthDefaultState();
    // Clear depth buffer
    // Set render targets
    // Clear render targets
    geometry_buffer_->PrepareDeferredRender();
    // Set culling back
    device_resources->SetCullBackSolidState();

    RenderActorsFromBuffer();
}

void DeferredRenderPass::RenderLights(std::vector<SceneActor*>& actors)
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    FilterByMaterialInBuffer<DeferredLightMaterial>(actors);

    device_resources->SetBlendOneOneState();

    constexpr float back_color[4] = { 0,0,0,1 };
    ID3D11RenderTargetView* view = device_resources->GetRenderTargetView();
    context->OMSetRenderTargets(1, &view, device_resources->GetDepthStencilView());
    context->ClearRenderTargetView(view, back_color);

    geometry_buffer_->SetTextures();

    RenderActorsFromBuffer();
}


void DeferredRenderPass::RenderActorsFromBuffer() const
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();

    Material* currentMaterial = actors_buffer[0]->GetRenderData()->GetMaterial();
    currentMaterial->PrepareRender();

    for (auto actor : actors_buffer)
    {
        std::shared_ptr<RenderData> renderData = actor->GetRenderData();
        Material* item_material = renderData->GetMaterial();
        if (item_material != currentMaterial)
        {
            // std::cout << "There is somehow different material, check it please!\n";
            currentMaterial = item_material;
            currentMaterial->PrepareRender();
        }

        currentMaterial->PrepareObjectData(actor);
        renderData->SetBuffers(context);
        context->DrawIndexed(renderData->GetIndicesCount(), 0, 0);
    }
}
