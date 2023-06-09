#include "SFML/graphics.hpp"
#include "Core/Engine.h"
#include "Entities/Player.h"
#include "Entities/Dummy.h"
#include "Entities/Enemy.h"

int main(int argc, char* args[])
{
	// Declare and get instance of singleton 
	Engine& GameEngine = Engine::GetInstance();
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	//create world so that we can add entities to it
	GameEngine.world = ECS::World::createWorld();
	//create our first entity 
	ECS::Entity* background;
	//ECS::Entity* myEnt;
	//ECS::Entity* tux;
	//Add systems to the engine
	GameEngine.AddSystem(new RenderingSystem());
	GameEngine.AddSystem(new AnimationSystem());
	GameEngine.AddSystem(new MovementSystem());
	GameEngine.AddSystem(new InputSystem());
	GameEngine.AddSystem(new PhysicsSystem());
	GameEngine.AddSystem(new TileMapSystem());
	
	background = GameEngine.world->create();
	background->assign <Transform>(0, 0, false);
	background->assign <Sprite2D>("../Debug/Pictures/bg.jpg");
	std::cout << "id: " << background->getEntityId() << std::endl;

	/*myEnt = GameEngine.world->create();
	myEnt->assign <Transform>(200, 300, true, 0.3f, 0.3f, 0.0f, 0.2f);
	myEnt->assign <Sprite2D>("../Debug/Pictures/herosheet.png");
	myEnt->assign <Animator>(32, 32, 200.0f, 4, 1);
	myEnt->assign <BoxCollider>();
	std::cout << "id: " << myEnt->getEntityId() << std::endl;

	tux = GameEngine.world->create();
	tux->assign <Transform>(400, 400, true, 0.3f, 0.3f, 0.0f, 0.2f);
	tux->assign <Sprite2D>("../Debug/Pictures/Tux_from_linux.png");
	tux->assign <Animator>(56, 72, 2000.0f, 3, 9);
	tux->assign <InputController>();
	tux->assign <BoxCollider>();
	tux->get<Animator>()->currentRow = 8;
	std::cout << "id: " << tux->getEntityId() << std::endl;*/

	//create instances of entities
	Entity* enemy_1 = new Enemy(sf::Vector2f(200.0f, 200.0f), 0.05f);
	Entity* dummy = new Dummy("../debug/pictures/BlueBox.png", sf::Vector2f(400.0f, 400.0f));
	Entity* player = new Player(sf::Vector2f(300.0f, 300.0f), 0.05f);




	// pass window refrence to Engine and start
	GameEngine.Start(&window);
	return 0;
}