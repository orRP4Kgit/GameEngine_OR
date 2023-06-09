#include "Tile.h"

Tile::Tile(float xPos, float yPos, float gridSizeF, bool bColliding)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setPosition(sf::Vector2f(xPos * gridSizeF, yPos * gridSizeF));
    this->bColliding = bColliding;
}

void Tile::Render(sf::RenderTarget& target) const
{
    target.draw(this->shape);
}

const bool& Tile::GetCollision() const
{
    return this->bColliding;
}

const sf::Vector2f& Tile::GetPosition() const
{
    return this->shape.getPosition();
}

std::string Tile::ToString() const
{
    std::stringstream stringForm;
    stringForm << this->bColliding << " ";
    return stringForm.str();
    
}
