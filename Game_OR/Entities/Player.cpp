#include "Player.h"

Player::Player(sf::Vector2f location, float speed) : Soldier("../debug/Pictures/Player_1.png", location, speed)
{
	entity->assign<InputController>();
	entity->get<Tag>()->AddTag("Player");
	entity->assign<TileMap>();
	entity->assign<Transform>(location.x, location.y, speed, speed, 0.0f, 0.05f);
	

}
