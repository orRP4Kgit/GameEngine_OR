#include "Engine.h"
#include "../Interface/PauseMenu.h"
#include "../Interface/States.h"
#include "../Interface/MainCamera.h"

Engine& Engine::GetInstance(void)
{
	static Engine instance;
	return instance;
}

void Engine::Start(sf::RenderWindow* window)
{
	bQuit = false;
	this->window = window;
	this->pauseMenu = new PauseMenu(window);
	this->mainCamera = new MainCamera(sf::Vector2f(static_cast<float>(this->window->getSize().x / 2), static_cast<float>(this->window->getSize().y / 2)));
	while (window->isOpen() == true)
	{
		Update();
	}
}

void Engine::AddSystem(ECS::EntitySystem* newSystem) const
{
	world->registerSystem(newSystem);
	world->enableSystem(newSystem);

}

void Engine::Update(void)
{
	sf::Event event;
	while (window->pollEvent(event) == true)
	{
		// Close requested event
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		this->pauseMenu->Update(event, this->deltaTime, this->window);
	}
	world->tick(this->deltaTime);
	this->mainCamera->Update(this->world, this->deltaTime, this->window);
	if (States::GetPausedState() == true)
	{
		this->OnPaused();
	}
}

void Engine::OnPaused() const
{
	PauseMenu::Render(window, deltaTime, mainCamera->cameraView.getCenter());
}
