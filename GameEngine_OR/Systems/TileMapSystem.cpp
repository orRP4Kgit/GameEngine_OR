#include "TileMapSystem.h"
#include "../Interface/Gui_Components/ButtonMap.h"
#include "../Interface/Gui_Components/Button.h"

void TileMapSystem::tick(ECS::World* world, float DeltaTime)
{
	if (States::GetPausedState() == false)
	{
		Engine::GetInstance().world->each<TileMap>(
			[&](ECS::Entity* entity, ECS::ComponentHandle<TileMap> tileMap) -> void 
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
				{
					this->AddTileOnClick(true, tileMap);
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
				{
					this->AddTileOnClick(false, tileMap);
				}

				if (ButtonMap::GetMap()["SAVE"]->bClicked == true)
				{
					tileMap->SaveTileMap("TileTest.txt");
					ButtonMap::GetMap()["SAVE"]->bClicked = false;
					std::cout << "SAVED" << std::endl;
				}

				if (ButtonMap::GetMap()["LOAD"]->bClicked == true)
				{
					tileMap->LoadTileMap("TileTest.txt");
					ButtonMap::GetMap()["LOAD"]->bClicked = false;
					std::cout << "LOADED" << std::endl;
				}

			});
	}
}

void TileMapSystem::AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<TileMap> tileMap) const
{
	//Refrence for window pointer to determine active cursor position for adding tiles

	sf::RenderWindow* winRef = Engine::GetInstance().window;
	sf::Vector2f mousePosView = winRef->mapPixelToCoords(sf::Mouse::getPosition(*winRef));
	sf::Vector2i mousePosGrid(static_cast<int>(mousePosView.x / tileMap->gridSizeF), static_cast<int>(mousePosView.y / tileMap->gridSizeF));
	tileMap->AddTile(mousePosGrid.x, mousePosGrid.y, 0, bHasCollision);
}
