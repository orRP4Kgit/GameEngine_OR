#include "AnimationSystem.h"
#include "../Interface/States.h"

void AnimationSystem::tick(ECS::World* world, float DeltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<Animator, Sprite2D>(
			[&](ECS::Entity* entity, ECS::ComponentHandle<Animator> animator, ECS::ComponentHandle<Sprite2D> sprite) -> void
			{
				//By default go to the next picture 
				animator->currentTime += DeltaTime;

		if (animator->currentTime >= animator->timeBetweenFrames)
		{
			animator->currentTime = 0;
			animator->currentColumn = (animator->currentColumn + 1) % animator->totalColumns;
		}

		sprite->self.setTextureRect(sf::IntRect(
			animator->currentColumn * animator->width,
			animator->currentRow * animator->height,
			animator->width,
			animator->height
		));
			}
		);
	}
	
}
