#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
	float delay;

public:
	Projectile(sf::Vector2f location, float angle, float speed);
	~Projectile();
};

