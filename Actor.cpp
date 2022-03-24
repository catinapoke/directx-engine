#include "Actor.h"
#include "ComponentBase.h"

Actor::~Actor()
{
    for (auto& pair : components)
        delete pair.second;
}

void Actor::Awake()
{
    for (auto& pair : components)
        pair.second->Awake();
}

void Actor::Start()
{
    for (auto& pair : components)
        pair.second->Start();
};

void Actor::Update(float deltaTime)
{
    for (auto& pair : components)
        pair.second->Update(deltaTime);
};

void Actor::SetActor(ComponentBase* component)
{
    component->actor = this;
}