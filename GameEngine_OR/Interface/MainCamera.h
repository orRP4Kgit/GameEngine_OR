#pragma once
#include "../Core/Engine.h"

class MainCamera
{
public:
	sf::View cameraView;
	MainCamera(sf::Vector2f pivot);
	~MainCamera() = default;
	void Update(ECS::World* world, float DeltaTime, sf::RenderWindow* window);
};

