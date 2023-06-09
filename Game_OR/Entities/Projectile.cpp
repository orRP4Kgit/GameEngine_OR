#include "Projectile.h"

Projectile::Projectile(sf::Vector2f location, float angle, float speed)
{
	const Engine& engine = Engine::GetInstance();
	entity = engine.world->create();
	entity->assign<Sprite2D>("delta/debug/pics/bullet_1.png");
	entity->assign<Tag>();
	entity->get<Tag>()->AddTag("Projectile");
	entity->assign<Transform>(location.x, location.y, speed, speed, angle);
	this->delay = 0.0f;
}

Projectile::~Projectile()
{
	const Engine& engine = Engine::GetInstance();
	engine.world->destroy(entity);
	

}
