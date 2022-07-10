#pragma once
#include "Actor.h"

class ComponentBase
{
public:
    ComponentBase() {}
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(float deltaTime) {};
    Actor* GetActor();
private:
    Actor* actor;
    friend class Actor;
};