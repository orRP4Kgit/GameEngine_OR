#pragma once
#include "../Core/Engine.h"

class RenderingSystem : public ECS::EntitySystem
{
private:
	std::unordered_map<std::string, sf::Texture*> textureMap;
public:
	RenderingSystem(void) = default;
	~RenderingSystem(void) = default;
	void tick(ECS::World* world, float deltaTime) override;

	

private:
	sf::Texture* LoadTexture(std:: string texturePath);
};

