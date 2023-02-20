#pragma once
#include<iostream>
#include"SFML/graphics.hpp"
#include "ECS.h"
#include "Components.h"
#include "../Systems/renderingSystem.h"
#include "../Systems/AnimationSystem.h"

class Engine
{
public:
	sf::RenderWindow* window{ nullptr };
	ECS::World* world{ nullptr };

private:
	bool bQuit;


private:
	Engine(void) = default;
	// required to prevent refrence from being copied, moved, or assigned
	Engine(Engine& copy); // hide copy constructer
	Engine(Engine&& other); // hide move constructer 
	Engine& operator= (Engine& copy); // hide assignment operator 
	~Engine(void) = default;


public:
	static Engine& GetInstance(void);
	void Start(sf::RenderWindow* window);
	void AddSystem(ECS::EntitySystem* newSystem);
private:
	void Update(void);



};

