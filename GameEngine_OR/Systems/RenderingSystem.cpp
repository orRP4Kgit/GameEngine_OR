#include "RenderingSystem.h"
#include "../Interface/States.h"

void RenderingSystem::tick(ECS::World* world, float deltaTime)
{


	if (States::GetPausedState() == false)
	{
		// clear before drawing all textures
		Engine::GetInstance().window->clear();

		world->each<Transform, Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite
				) -> void
			{
				// ADD texture to map
				if (textureMap.count(sprite->texturePath) < 1)
				{
					textureMap[sprite->texturePath] = LoadTexture(sprite->texturePath);
				}
		// if no texture is found, add it
		if (sprite->self.getTexture() == nullptr)
		{
			sprite->self.setTexture(*textureMap[sprite->texturePath]);
			sprite->width = sprite->self.getGlobalBounds().width;
			sprite->height = sprite->self.getGlobalBounds().height;
		}
		// Update and draw to screen
		sprite->self.setPosition(transform->xPos, transform->yPos);
		Engine::GetInstance().window->draw(sprite->self);
		/*if (std::to_string(entity->getEntityId()) == "4")
		{
			std::cout << entity->get<Transform>()->xPos<< std::endl;
			}
		*/});

		world->each<TileMap>(
			[&](ECS::Entity*, ECS::ComponentHandle<TileMap> tileMap)->void
			{
				//Loop through each tile and render onto the Engine's window instance
				for (auto& x : tileMap->map)
				{
					for (auto& y : x)
					{
						for (const auto& z : y)
						{
							if (z == nullptr)
							{
								continue;
							}

							sf::RenderWindow* winRef = Engine::GetInstance().window;
							winRef->draw(z->shape);
							if (z->GetCollision() == true)
							{
								tileMap->collisionBox.setPosition(z->GetPosition());
								winRef->draw(tileMap->collisionBox);
							}
						}
					}
				}

			});



		// Display updates
		Engine::GetInstance().window->display();
	}
}

sf::Texture* RenderingSystem::LoadTexture(std::string texturePath)
{
	sf::Texture* tex = new sf::Texture();
	if (tex->loadFromFile(texturePath) == false)
	{
		std::cerr << "unable to load image " << texturePath << "./nIs this image in the correct directory?" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	else
	{
		return tex;
	}

}
