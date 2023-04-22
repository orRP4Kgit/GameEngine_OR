#pragma once
#include "Entity.h"
class Soldier : public Entity
{
private:
	int fireDelay = 0;
public:
	Soldier(std::string picturePath, sf::Vector2f location);
	~Soldier() = default;

	
};

