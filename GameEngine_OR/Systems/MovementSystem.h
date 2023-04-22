#pragma once

#include "../Core/Engine.h"

class MovementSystem : public ECS::EntitySystem
{
private:
	float timer{ 0.0f };

public:
	MovementSystem() = default;
	~MovementSystem() = default;

	void tick(ECS::World* world, float deltaTime) override;
};

