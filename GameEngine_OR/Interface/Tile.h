#include "sfml/Graphics.hpp"
#include "sfml/System.hpp"
#include <sstream>

class Tile
{
public:
	bool bColliding;
	sf::RectangleShape shape;

	Tile(float xPos, float yPos, float gridSizeF, bool bColliding);
	~Tile() = default;

	void Render(sf::RenderTarget& target) const;
	const bool& GetCollision() const;
	const sf::Vector2f& GetPosition() const;
	std::string ToString() const;
};
