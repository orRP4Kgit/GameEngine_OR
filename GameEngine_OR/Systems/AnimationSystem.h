#pragma once
#include "../Core/Engine.h"

class AnimationSystem : public ECS:: EntitySystem
{
public:
	AnimationSystem() = default;
	~AnimationSystem() = default;
	void tick(ECS::World* world, float DeltaTime) override;
};

