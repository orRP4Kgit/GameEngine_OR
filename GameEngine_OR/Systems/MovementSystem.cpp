#define _USE_MATH_DEFINES
#include "MovementSystem.h"
#include <cmath>
void MovementSystem::tick(ECS::World* world, float DeltaTime)
{
	world->each<InputController, Transform, Sprite2D, Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController> input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite2D> sprite,
			ECS::ComponentHandle<Animator> animat)-> void
		{
			//centre anchor point to sprite
			//sprite->self.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));
			//ECS::ComponentHandle<InputController> input = entity->get<InputController>();
			if (input->bInputActive == true)
			{
				if (input->w == true)
				{
					transform->xSpeed = sin((sprite->self.getRotation() + 90.0f) / 180.0f* M_PI) * transform-> ySpeedMod;
					transform->ySpeed = -cos((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform-> ySpeedMod;
					transform->Move();
				}
				else if (input->s == true)
				{
					transform->xSpeed = -sin((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->ySpeedMod;
					transform->ySpeed = cos((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->ySpeedMod;
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
		});
}
