#include "KatamariPicker.h"
#include "SphereCollider.h"
#include "Game.h"
#include "SceneActor.h"
#include "TransformComponent.h"

void KatamariPicker::Awake()
{
    ComponentBase::Awake();
    self_collider = GetActor()->GetComponent<SphereCollider>();
    assert(self_collider != nullptr && "Katamari picker requires sphere collider!");

    const std::vector<SceneActor*>& actors = *(Game::GetCurrentGame()->GetSceneActors());
    for (auto scene_actor : actors)
    {
        SphereCollider* collider = scene_actor->GetActor()->GetComponent<SphereCollider>();
        if (collider != nullptr && collider != self_collider)
            colliders_.push_back(collider);
    }
}

void KatamariPicker::Update(float deltaTime)
{
    ComponentBase::Update(deltaTime);

    for (auto it = colliders_.begin(); it != colliders_.end(); it++)
    {
        SphereCollider* collider = *it;

        if (self_collider->IsOverlapping(*collider))
        {
            if (collider->GetRadius() > self_collider->GetRadius()) continue;

            self_collider->AppendRadiusByArea(*collider);
            collider->GetActor()->GetComponent<TransformComponent>()->SetParent(GetActor()->GetComponent<TransformComponent>());
            collider->GetActor()->RemoveComponent<SphereCollider>();

            *it = nullptr;
        }
    }

    colliders_.erase(std::remove(colliders_.begin(), colliders_.end(), nullptr), colliders_.end());
}
