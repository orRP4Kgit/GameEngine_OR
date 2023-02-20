#include "SFML/graphics.hpp"
#include "Core/Engine.h"

int main(int argc, char* args[])
{
	// Declare and get instance of singleton 
	Engine& GameEngine = Engine::GetInstance();
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	//create world so that we can add entities to it
	GameEngine.world = ECS::World::createWorld();
	//create our first entity 
	ECS::Entity* myEnt;
	//Add systems to the engine
	GameEngine.AddSystem(new RenderingSystem());
	GameEngine.AddSystem(new AnimationSystem());

	//create 250 entities to the world
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			myEnt = GameEngine.world->create();
			myEnt->assign <Transform>(i * 25, j * 32);
			myEnt->assign <Sprite2D>("../Debug/Pictures/herosheet.png");
			myEnt->assign <Animator>(32, 32, 200.0f, 4, 1);
			std::cout << "id: " << myEnt->getEntityId() << std::endl;
		}
	}


	// pass window refrence to Engine and start
	GameEngine.Start(&window);
	return 0;
}