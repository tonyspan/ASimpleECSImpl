#include "pch.h"

#include "Entity.h"

EntityType Entity::s_IdRefCount = 0;

EntityType Entity::GetId() const 
{
	return m_Id;
}

Entity::Entity()
{
	m_Id = s_IdRefCount++;
}
