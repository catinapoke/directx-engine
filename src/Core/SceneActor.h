#pragma once
#include <memory>
#include "../RenderData/RenderData.h"

class Actor;
class TransformComponent;

class SceneActor
{
public:
    SceneActor(Actor* actor, std::shared_ptr<RenderData> data);
    void Awake();

    Actor* GetActor() const { return actor; }
    TransformComponent* GetTransform() const { return transform; }
    std::shared_ptr<RenderData> GetRenderData() { return renderData; }

private:
    TransformComponent* transform;
    std::shared_ptr<RenderData> renderData;
    Actor* actor;
};