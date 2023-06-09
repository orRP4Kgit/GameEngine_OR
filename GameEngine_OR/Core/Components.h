#pragma once
#include "Engine.h"
#include "../Interface/Tile.h"
#include "../Interface/States.h"
#include <fstream>
#include <iostream>



struct Transform
{
public:
	ECS_DECLARE_TYPE; 
	float xPos, yPos;
	float rotationAngle;
	float rotationSpeed;
	float xSpeed, ySpeed;
	float xSpeedMod, ySpeedMod;
	bool bCollide;

	Transform(float xPos, float yPos, float xSpeed = 0.0f, float ySpeed = 0.0f, float rotationAngle = 0.0f, float rotationSpeed = 0.0f)
	{
		this->xPos = xPos;
		this->yPos = yPos;
		this->xSpeed = xPos;
		this->ySpeed = yPos;
		this->xSpeedMod = xSpeed;
		this->ySpeedMod = ySpeed;
		this->rotationAngle = rotationAngle;
		this->rotationSpeed = rotationSpeed;
		this->bCollide = false;

		

	}

	void Move()
	{
		if (bCollide == false)
		{
			this->xPos += xSpeed;
			this->yPos += ySpeed;
		}
	}
}; 
ECS_DEFINE_TYPE(Transform)

struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;
	sf::Sprite self;
	std::string texturePath;
	float width, height;

	Sprite2D(std::string texturePath)
	{
		this->texturePath = texturePath;

	}
};
ECS_DEFINE_TYPE(Sprite2D);

struct Animator
{
public:
	ECS_DECLARE_TYPE;
	int width, height, currentColumn, currentRow, totalColumns, totalRows;
	float currentTime, timeBetweenFrames;
	Animator(int width, int height, float timeBetweenFrames, int columns, int rows)
	{
		currentColumn = 0;
		currentRow = 0;
		totalColumns = columns;
		totalRows = rows;
		currentTime = 0.0f;
		this->width = width;
		this-> height = height;
		this->timeBetweenFrames = timeBetweenFrames;

	}


	
}; ECS_DEFINE_TYPE(Animator)

struct InputController
{
public:
	ECS_DECLARE_TYPE;

	bool bInputActive;
	bool w, a, s, d, left, right, up, down, space;

	InputController()
	{
		std::memset(this, false, sizeof(InputController));
		this->bInputActive = true;
	}
	
}; ECS_DEFINE_TYPE(InputController)

struct BoxCollider
{
public: 
	ECS_DECLARE_TYPE;
	float leftEdge, rightEdge, topEdge, bottomEdge;
	BoxCollider() 
	{
		std::memset(this, 0.0f, sizeof(BoxCollider));

	}

	void Update(float x, float y, float width, float height)
	{
		this->leftEdge = x;
		this->rightEdge = x + width;
		this->topEdge = y;
		this->bottomEdge = y + height;
	}

	

}; ECS_DEFINE_TYPE(BoxCollider)

struct Tag
{
public:
	ECS_DECLARE_TYPE;
	std::vector<std::string> tagNames;
	Tag() = default;
	
	void AddTag(std::string tag)
	{
		this->tagNames.push_back(tag);
	}

	bool ContainsTag(std::string tag)
	{
		return std::find(this->tagNames.begin(), this->tagNames.end(), tag) != this->tagNames.end();
	}

} ECS_DEFINE_TYPE(Tag);


struct Shooter
{
public:
	ECS_DECLARE_TYPE;
	float fireDelay, timeSinceLastShot;

} ECS_DEFINE_TYPE(Shooter);

struct TileMap
{
public:
	ECS_DECLARE_TYPE;
	float gridSizeF;
	uint32_t gridSizeU;
	uint32_t layers;
	sf::Vector2u maxSize;
	sf::RectangleShape collisionBox;
	std::vector<std::vector<std::vector<Tile*>>> map;

	TileMap()
	{
		this->gridSizeF = 50.0f;
		this->gridSizeU = static_cast<uint32_t>(this->gridSizeF);
		this->maxSize.x = 20;
		this->maxSize.y = 20;
		this->layers = 1;
		this->map.resize(this->maxSize.x);
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y);
				this->map[x].push_back(std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers);
					this->map[x][y].push_back(nullptr);
				}
			}
		}

		this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
		this->collisionBox.setFillColor(sf::Color::Magenta);
		this->collisionBox.setOutlineColor(sf::Color::Yellow);
		this->collisionBox.setOutlineThickness(-1.0f);

		
	}

	~TileMap()
	{
		this->Clear();
		
	}

	void AddTile(const uint32_t x, const uint32_t y, const uint32_t z, bool bHasCollision)
	{
		if (States::GetPausedState() == false)
		{
			printf("%d, %d, %d\n", maxSize.x, maxSize.y, layers);

			if (x < this->maxSize.x && x >= 0 &&
				y < this->maxSize.y && y >= 0 &&
				z < this->layers && z >= 0)
			{
				if (this->map[x][y][z] == nullptr)
				{
					this->map[x][y][z] = new Tile(x, y, this->gridSizeF, bHasCollision);
					std::cout << "Tile Added"<< std::endl;
				}
			}
		}
	}

	void Clear()
	{
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					delete this->map[x][y][z];
					this->map[x][y][z] = nullptr;
				}

				this->map[x][y].clear();
			}

			this->map[x].clear();
		}

		this->map.clear();
	}

	void SaveTileMap(std::string fileName)
	{
		std::ofstream saveFile;
		saveFile.open(fileName);

		if (saveFile.is_open() == true)
		{
			saveFile << this->maxSize.x << " " << this->maxSize.y << "\n" << this->gridSizeF << "\n" << this->layers << "\n";


			for (size_t x = 0; x < this->maxSize.x; x++)
			{
				for (size_t y = 0; y < this->maxSize.y; y++)
				{
					for (size_t z = 0; z < this->layers; z++)
					{
						if (this->map[x][y][z] != nullptr) 
						{
							saveFile << x << " " << y << " " << z << " " << this->map[x][y][z]->ToString() << "\n";
						}
						
					}

				}
			}
		}
		else
		{
			std::cerr << "Error tileMap could not save to file " << fileName << std::endl;
		}

		saveFile.close();
	}

	void LoadTileMap(std::string fileName)
	{
		std::printf("Loading TileMap\n");
		std::ifstream loadFile;
		loadFile.open(fileName);

		if (loadFile.is_open() == true)
		{
			loadFile >> this->maxSize.x >> this->maxSize.y >> this->gridSizeF >> this->layers;
			this->gridSizeU = static_cast<uint32_t>(this->gridSizeF);
			this->Clear();
			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());


			for (size_t x = 0; x < this->maxSize.x; x++)
			{
				for (size_t y = 0; y < this->maxSize.y; y++)
				{

					this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

					for (size_t z = 0; z < this->layers; z++)
					{
						this->map[x][y].resize(this->layers, nullptr);
					}
				}
			}

			int tx, ty, tz;
			bool bColliding = false;

			while (loadFile >> tx >> ty >> tz >> bColliding)
			{
				std::printf("Reading %d, %d, %d\n", tx, ty, tz);
				this->map[tx][ty][tz] = new Tile(tx, ty, this->gridSizeF, bColliding);
			}
		}
		else
		{
			std::cerr << "Error TileMap could not load from file " << fileName << std::endl;
		}

		loadFile.close();
	}



} ECS_DEFINE_TYPE(TileMap);