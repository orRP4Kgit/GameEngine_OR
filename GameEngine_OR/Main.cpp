#include "SFML/graphics.hpp"
#include "Core/Engine.h"

int main(int argc, char* args[])
{
	// Declare and get instance of singleton 
	Engine& GameEngine = Engine::GetInstance();
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");
	// pass window refrence to Engine and start
	GameEngine.Start(&window);
	return 0;
}