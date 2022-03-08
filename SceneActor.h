#pragma once
#include "Actor.h"
#include "TransformComponent.h"
#include "RenderData.h"

class SceneActor : Actor
{
public:
    SceneActor(TransformComponent* component, RenderData* data):transform(component), renderData(data), Actor()
    {

    }

    void Awake() override
    {
        AddComponent<TransformComponent>(transform); 
        Actor::Awake();
    }

    TransformComponent* GetTransform() { return transform; }
    RenderData* GetRenderData() { return renderData; }

private:
    TransformComponent* transform;
    RenderData* renderData;
};