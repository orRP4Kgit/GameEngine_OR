#pragma once
#include "Entity.h"
#include "Core/Engine.h"

class Dummy : public Entity
{
public: 
	Dummy(std::string picturePath, sf::Vector2f location);
	~Dummy() = default;


};

