#include "pch.h"

#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"

int main()
{
	EntityManager registry;

	auto e1 = registry.CreateEntity();
	e1->AddComponent<TagComponent>(TagComponent{ "e1" });
	e1->AddComponent<HealthComponent>(HealthComponent{ 100, 80 });
	
	registry.AddEntity(e1);

	auto e2 = registry.CreateEntity();
	e2->AddComponent<TagComponent>(TagComponent{ "e2" });
	e2->AddComponent<TransformComponent>();
	e2->AddComponent<CameraComponent>();

	registry.AddEntity(e2);

	auto e3 = registry.CreateEntity();
	e3->AddComponent<TagComponent>(TagComponent{ "e3" });
	e3->AddComponent<TransformComponent>();
	e3->AddComponent<SpriteRendererComponent>(vec4{ 2.0f, 2.0f, 2.0f, 2.0f });
	
	// Assertion
	// e3->AddComponent<TagComponent>();

	registry.AddEntity(e3);

	auto tc = registry.GetAllEntitiesWithComponent<TagComponent>();

	std::cout << "Entities with single component (tag): " << tc.size() << std::endl;

	for (auto entity : tc)
	{
		std::cout << "Entity idx: " << entity->GetId() << " tag: " << entity->GetComponent<TagComponent>()->Tag << std::endl;
	}

	auto th = registry.GetAllEntitiesWithComponents<TagComponent, HealthComponent>();

	std::cout << "Entities with multiple components (tag, health): " << th.size() << std::endl;

	for (auto entity : th)
	{
		std::cout << "Entity idx: " << entity->GetId() << " current health: " << entity->GetComponent<HealthComponent>()->CurrentHealth << std::endl;
	}

	std::cout << "Removing component (health) from all entities with multiple components (tag, health)" << std::endl;

	for (auto entity : th)
	{
		entity->RemoveComponent<HealthComponent>();
		std::cout << "Entity idx: " << entity->GetId() << " has component (health)? " << std::boolalpha << entity->HasComponent<HealthComponent>() << std::endl;
	}

	// For example in a Renderer 
	// auto renderables = registry.GetAllEntitiesWithComponents<TransformComponent, SpriteRendererComponent>();
	// for (auto r : renderables)
	// {
	//	 DrawEntity(r);
	// }
}