#pragma once

#include "Entity.h"

class EntityManager
{
public:

    EntityManager() = default;

    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(EntityManager& other) = delete;

    void AddEntity(std::unique_ptr<Entity>& e);

    std::unique_ptr<Entity> CreateEntity()
    {
        return std::make_unique<Entity>();
    }

    template <typename T>
    auto GetAllEntitiesWithComponent()
    {
        std::vector<Entity*> returnVec;

        for(auto& entity : m_Entities)
        {
            if (entity->HasComponent<T>())
                returnVec.push_back(entity.get());
        }

        return returnVec;
    }

    template <typename... T>
    auto GetAllEntitiesWithComponents()
    {
        std::vector<Entity*> returnVec;

        for(auto& entity : m_Entities)
        {
            if (entity->HasComponents<T...>())
                returnVec.push_back(entity.get());
        }

        return returnVec;
    }
private:
    std::vector<std::unique_ptr<Entity>> m_Entities;
};
