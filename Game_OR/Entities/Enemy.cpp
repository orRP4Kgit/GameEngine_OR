#include "Enemy.h"

Enemy::Enemy(sf::Vector2f location, float speed) : Soldier("../debug/pictures/enemy_1.png", location, speed)
{
	entity->get<Tag>()->AddTag("Enemy");
	entity->get<Transform>()->xSpeed = speed;
	entity->get<Transform>()->ySpeed = speed;
}

