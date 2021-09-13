#include "pch.h"

#include "EntityManager.h"

void EntityManager::AddEntity(std::unique_ptr<Entity>& e)
{
    m_Entities.push_back(std::move(e));
}