#pragma once

#include "Component.h"

class Entity
{
public:
    EntityType GetId() const;

    Entity();

    template <typename T, typename... Args>
    T* AddComponent(Args&&... rest)
    {
        assert(!HasComponent<T>() && "Entity already has component");

        auto component = std::make_unique<T>(std::forward<Args>(rest)...);

        component->CompId = ComponentBase::GetComponentID<T>();

        m_Components.push_back(std::move(component));

        return static_cast<T*>(m_Components.back().get());
    }

    template <typename T>
    T* GetComponent() const
    {
        assert(HasComponent<T>() && "Entity does not have component");

        auto found = std::find_if(m_Components.begin(), m_Components.end(), [](const auto& component) { return component->CompId == ComponentBase::GetComponentID<T>(); });

        if (found != m_Components.end())
            return static_cast<T*>((*found).get());

        return nullptr;
    }

    template <typename T>
    void RemoveComponent()
    {
        assert(HasComponent<T>() && "Entity does not have component");

        auto found = std::remove_if(m_Components.begin(), m_Components.end(), [](const auto& component) { return component->CompId == ComponentBase::GetComponentID<T>(); });

        m_Components.erase(found);
    }

    template <typename T>
    bool HasComponent() const
    {
        auto found = std::find_if(m_Components.begin(), m_Components.end(), [](const auto& component) { return component->CompId == ComponentBase::GetComponentID<T>(); });

        if (found != m_Components.end())
            return true;

        return false;
    }

    template <typename... T>
    bool HasComponents() const
    {
        if ((HasComponent<T>() && ...))
            return true;

        return false;
    }
private:
    static EntityType s_IdRefCount;
    EntityType m_Id;
    std::vector<std::unique_ptr<ComponentBase>> m_Components;
};
