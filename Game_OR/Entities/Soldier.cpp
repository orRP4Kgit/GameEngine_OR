#include "Soldier.h"

Soldier::Soldier(std::string picturePath, sf::Vector2f location)
{
	Engine& engine = Engine::GetInstance();
	entity = engine.world->create();
	entity->assign<Sprite2D>(picturePath);
	entity->assign<Transform>(location.x, location.y, 0.03f, 0.03f, 0.0f, 0.05f);
	entity->assign <BoxCollider>();


}
