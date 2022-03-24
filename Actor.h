#pragma once
#include <assert.h>
#include <unordered_map>
#include <typeindex>

class ComponentBase;

class Actor
{
public:
    Actor() {};
    virtual ~Actor();

    virtual void Awake();
    virtual void Start();
    virtual void Update(float deltaTime);

    template<typename T>
    T* GetComponent()
    {
        static_assert(std::is_base_of<ComponentBase, T>::value, "ComponentType is not derived from ComponentBase");

        auto iterator = components.find(std::type_index(typeid(T)));
        if (iterator != components.end())
            return (T*)iterator->second;

        return nullptr;
    }

    template<typename T>
    void AddComponent(T* component)
    {
        static_assert(std::is_base_of<ComponentBase, T>::value, "ComponentType is not derived from ComponentBase");

        auto iterator = components.find(std::type_index(typeid(T)));
        assert(iterator == components.end() && "Can't add already existing component");
        ComponentBase* c = dynamic_cast<ComponentBase*>(component);
        c->actor = this;
        components[std::type_index(typeid(T))] = c;
    }

    template<typename T>
    T* AddComponent()
    {
        static_assert(std::is_base_of<ComponentBase, T>::value, "ComponentType is not derived from ComponentBase");

        auto iterator = components.find(std::type_index(typeid(T)));
        assert(iterator == components.end() && "Can't add already existing component");
        T* c = new T();
        SetActor(c);
        components[std::type_index(typeid(T))] = c;

        return c;
    }

private:
    void SetActor(ComponentBase* component);

private:
    std::unordered_map<std::type_index, ComponentBase*> components;
};