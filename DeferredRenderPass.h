#pragma once
#include "RenderPass.h"

class GeometryBuffer;

class DeferredRenderPass : public RenderPass
{
public:
    DeferredRenderPass(std::shared_ptr<DeviceResources> resources);

    void Render(std::vector<SceneActor*>& actors) override;

protected:
    void RenderObjects(std::vector<SceneActor*>& actors);
    void RenderLights(std::vector<SceneActor*>& actors);
    void RenderActorsFromBuffer() const;

    template<class T>
    void FilterByMaterialInBuffer(std::vector<SceneActor*>& actors);

protected:
    std::vector<SceneActor*> actors_buffer;
    GeometryBuffer* geometry_buffer_;
};

template <class T>
void DeferredRenderPass::FilterByMaterialInBuffer(std::vector<SceneActor*>& actors)
{
    static_assert(std::is_base_of<Material, T>::value, "Type is not derived from Material");

    actors_buffer.clear();
    for (auto actor : actors)
    {
        T* material = dynamic_cast<T*>(actor->GetRenderData()->GetMaterial());
        if (material != nullptr)
            actors_buffer.push_back(actor);
    }
}
