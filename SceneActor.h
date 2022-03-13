#pragma once
#include <memory>
#include "RenderData.h"

class Actor;
class TransformComponent;

class SceneActor
{
public:
    SceneActor(Actor* actor, std::shared_ptr<RenderData> data);
    void Awake();

    TransformComponent* GetTransform() { return transform; }
    std::shared_ptr<RenderData> GetRenderData() { return renderData; }

private:
    TransformComponent* transform;
    std::shared_ptr<RenderData> renderData;
    Actor* actor;
};