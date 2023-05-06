#define _USE_MATH_DEFINES
#include "MovementSystem.h"
#include "../Interface/States.h"
#include <cmath>

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	this->timer += deltaTime;

	if (States::GetPausedState() == false)
	{
		world->each<InputController, Transform, Sprite2D, Tag>(
			[&](ECS::Entity*,
				ECS::ComponentHandle<InputController> input,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Tag> tag
				) -> void
			{
				// Center anchor point to sprite
				sprite->self.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));

		//const ECS::ComponentHandle<InputController> input = entity->get<InputController>();
		if (tag->ContainsTag("Player") == true)
		{
			if (input->bInputActive == true)
			{
				if (input->w == true)
				{
					transform->xSpeed = sin((sprite->self.getRotation() + 90.0) / 180.0 * M_PI) * transform->ySpeedMod;
					transform->ySpeed = -cos((sprite->self.getRotation() + 90.0) / 180.0 * M_PI) * transform->ySpeedMod;

					transform->Move();
				}
				else if (input->s == true)
				{
					transform->xSpeed = -sin((sprite->self.getRotation() + 90.0) / 180.0 * M_PI) * transform->ySpeedMod;
					transform->ySpeed = cos((sprite->self.getRotation() + 90.0) / 180.0 * M_PI) * transform->ySpeedMod;

					transform->Move();
				}
				else
				{
					transform->xSpeed = 0;
					transform->ySpeed = 0;
				}

				if (input->a == true)
				{
					sprite->self.rotate(-transform->rotationSpeed);
				}
				else if (input->d == true)
				{
					sprite->self.rotate(transform->rotationSpeed);
				}
			}
		}
		else if (tag->ContainsTag("Projectile") == true)
		{

		}
			});
	}
}
