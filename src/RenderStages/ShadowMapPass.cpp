#include "ShadowMapPass.h"

#include "../Materials/ShadowCastMaterial.h"
#include "../Components/LightComponent.h"
#include "../Components/Camera.h"
#include "../Utils/ShadowMap.h"

ShadowMapPass::ShadowMapPass(std::shared_ptr<DeviceResources> resources, CameraComponent* camera, LightComponent* light, int shadow_map_width, int shadow_map_height)
    :RenderPass(resources),
    shadow_map_material(new ShadowCastMaterial(resources, camera, light)),
    shadow_map(new ShadowMap(resources->GetDevice(), shadow_map_width, shadow_map_height))
{

}

void ShadowMapPass::Render(std::vector<SceneActor*>& actors)
{
    ID3D11DeviceContext* context = device_resources->GetDeviceContext();
    shadow_map->SetRenderTarget(context, 0);
    shadow_map->SetSampler(context);
    shadow_map_material->PrepareRender();

    for (SceneActor* item : actors)
    {
        InputScheme scheme = item->GetRenderData()->GetMaterial()->GetInputScheme();
        if (!InputLayoutSchemes::AreEqual(scheme, InputLayoutSchemes::PositionTexture) 
            && !InputLayoutSchemes::AreEqual(scheme, InputLayoutSchemes::PositionTextureNormal))
            continue;

        shadow_map_material->PrepareObjectData(item);

        std::shared_ptr<RenderData> renderData = item->GetRenderData();
        renderData->SetBuffers(context);
        context->DrawIndexed(renderData->GetIndicesCount(), 0, 0);
    }

    context->OMSetRenderTargets(0, nullptr, nullptr);
    shadow_map->SetTexture(context, 1);
}

ShadowMapPass::~ShadowMapPass()
{
    delete shadow_map_material;
    delete shadow_map;
}
