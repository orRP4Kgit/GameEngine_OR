#pragma once
#include "Soldier.h"
class Player : public Soldier
{
public:
	Player(sf::Vector2f location, float speed);
	~Player() = default;


};

