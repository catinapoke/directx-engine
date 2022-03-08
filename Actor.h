#pragma once
#include <assert.h>
#include <unordered_map>
#include <typeindex>
#include "ComponentBase.h"

class Actor
{
public:
    virtual void Awake() 
    {
        for (auto& pair : components)
            pair.second->Awake();
    };

    virtual void Start()
    {
        for (auto& pair : components)
            pair.second->Start();
    };

    virtual void Update(float deltaTime)
    {
        for (auto& pair : components)
            pair.second->Update(deltaTime);
    };

    template<typename T>
    T* GetComponent()
    {
        static_assert(std::is_base_of<ComponentBase, T>::value, "ComponentType is not derived from ComponentBase");

        auto iterator = components.find(std::type_index(T));
        if (iterator != components.end())
            return (*iterator).second;

        return nullptr;
    }

    template<typename T>
    void AddComponent(T* component)
    {
        static_assert(std::is_base_of<ComponentBase, T>::value, "ComponentType is not derived from ComponentBase");

        auto iterator = components.find(std::type_index(T));
        assert(iterator == components.end() && "Can't add already existing component");
        components[std::type_index(T)] = component;
    }

private:
    std::unordered_map<std::type_index, ComponentBase*> components;
};