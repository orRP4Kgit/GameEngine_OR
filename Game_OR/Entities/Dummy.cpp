#include "Dummy.h"

Dummy::Dummy(std::string picturePath, sf::Vector2f location)
{
	const Engine& engine = Engine::GetInstance();
	entity = engine.world->create();
	entity->assign<Sprite2D>(picturePath);
	entity->assign<Transform>(location.x, location.y);
	entity->assign<BoxCollider>();
	entity->assign<Tag>();
	entity->get<Tag>()->AddTag("Object");
}
