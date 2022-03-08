#pragma once
class ComponentBase
{
public:
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(float deltaTime) {};
};