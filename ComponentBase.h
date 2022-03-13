#pragma once

class Actor;

class ComponentBase
{
public:
    ComponentBase(Actor* owner):actor(owner) {}
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(float deltaTime) {};
    Actor* GetActor();
private:
    Actor* actor;
};