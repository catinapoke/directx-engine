#pragma once
#include <assert.h>
#include <unordered_map>
#include <typeindex>

class ComponentBase;

template<typename Base, typename T>
inline bool instance_of(const T* t) {
    return dynamic_cast<const Base*>(t) != nullptr;
}

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

        const auto iterator = components.find(std::type_index(typeid(T)));
        if (iterator != components.end())
            return static_cast<T*>(iterator->second);

        for(auto item : components)
        {
            if (instance_of<T>(item.second)) return static_cast<T*>(item.second);
        }

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

    template<typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<ComponentBase, T>::value, "ComponentType is not derived from ComponentBase");

        auto iterator = components.find(std::type_index(typeid(T)));
        assert(iterator != components.end() && "Can't remove non-existing component");

        T* component = nullptr;
        if(iterator == components.end())
        {
            for (auto item : components)
            {
                if (instance_of<T>(item.second))
                {
                    component = dynamic_cast<T*>(item.second);
                    components.erase(item.first);
                    break;
                }
            }
        }
        else
        {
            component = dynamic_cast<T*>(iterator->second);
            components.erase(iterator);
        }

        delete component;
    }

private:
    void SetActor(ComponentBase* component);

private:
    std::unordered_map<std::type_index, ComponentBase*> components;
};