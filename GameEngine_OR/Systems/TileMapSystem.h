#pragma once
#include "../Core/Engine.h"

class TileMapSystem : public ECS::EntitySystem
{
public:

	TileMapSystem() = default;
	~TileMapSystem() = default;

	void tick(ECS::World* world, float DeltaTime);
	void AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<TileMap> tileMap) const;


};

