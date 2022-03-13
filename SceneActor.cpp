#include "SceneActor.h"
#include "Actor.h"
#include "TransformComponent.h"

SceneActor::SceneActor(Actor* actor, std::shared_ptr<RenderData> data) : actor(actor), renderData(data)
{
    transform = actor->GetComponent<TransformComponent>();
    assert(transform != nullptr);
}

void SceneActor::Awake()
{
    actor->AddComponent<TransformComponent>(transform);
    actor->Awake();
}

