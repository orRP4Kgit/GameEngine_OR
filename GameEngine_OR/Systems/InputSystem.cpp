#include "InputSystem.h"
#include "../Interface/States.h"

InputSystem::InputSystem(sf::RenderWindow* window)
{
	this->window = window;
}

void InputSystem::tick(ECS::World* world, float DletaTime)
{
	this->GetKeyEvents(world);
}

void InputSystem::GetKeyEvents(ECS::World* world)
{
	if (States::GetPausedState() == false)
	{
		world->each<InputController>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<InputController>input) -> void
			{
				input->w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		input->a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		input->s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		input->d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

		input->left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		input->right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		input->down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		input->up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		input->space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			}
		);
	}
}
