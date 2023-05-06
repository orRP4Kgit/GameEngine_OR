#pragma once
#include "../Core/engine.h"

class ButtonMap;
class States;
class Button;

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow* window);
	~PauseMenu() = default;
	void Update(sf::Event event, float DeltaTime, sf::RenderWindow* window) const;
	static void  Render(sf::RenderWindow* window, float DeltaTime, sf::Vector2f resumePosition);

private:
	static void InitButtons();
	static void Quit(sf::RenderWindow* window);
};

