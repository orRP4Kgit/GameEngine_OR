#define _USE_MATH_DEFINES
#include "MovementSystem.h"
#include "../Interface/States.h"
#include <cmath>
#include <random>

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	this->timer += deltaTime;

	if (States::GetPausedState() == false)
	{
		world->each<Transform, Sprite2D, Tag>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Tag> tag
				) -> void
			{
				// Center anchor point to sprite
				sprite->self.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));

		
		if (tag->ContainsTag("Player") == true)
		{
			const ECS::ComponentHandle<InputController> input = entity->get<InputController>();

			if (input->bInputActive == true)
			{
				if (input->w == true)
				{
					transform->xSpeed = static_cast<float>(
						sin((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->xSpeedMod)
						);
					transform->ySpeed = static_cast<float>(
						-cos((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->ySpeedMod)
						);

					transform->Move();
				}
				else if (input->s == true)
				{
					transform->xSpeed = static_cast<float>(
						-sin((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->xSpeedMod)
						);
					transform->ySpeed = static_cast<float>(
						cos((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->ySpeedMod)
						);

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
		else if (tag->ContainsTag("Projectile") == true || tag->ContainsTag("Object") == true)
		{
			transform->xSpeed = static_cast<float>(
				sin((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->xSpeedMod)
				);
			transform->ySpeed = static_cast<float>(
				-cos((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->ySpeedMod)
				);

			transform->Move();
		}
		else if (tag->ContainsTag("Enemy") == true)
		{
			transform->xSpeed = static_cast<float>(
				sin((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->xSpeedMod) /2
				);
			transform->ySpeed = static_cast<float>(
				-cos((static_cast<double>(sprite->self.getRotation()) + 90.0) / 180.0 * M_PI) * static_cast<double>(transform->ySpeedMod) /2
				);

			transform->Move();

			//random rotation
			if (this->timer > 30000.0f)
			{
				//int random = (rand() % 360) + 1;
				//int random = std::uniform_int_distribution<int>(1, 360)(std::random_device{}());

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distribution(1, 360);

				int random = distribution(gen);

				sprite->self.setRotation(random + 90.0f);
				this->timer = 0.0f;
			}
		}
			});
	}
}
