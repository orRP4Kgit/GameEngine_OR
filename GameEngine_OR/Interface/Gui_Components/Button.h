#pragma once
#include "../../Core/Engine.h"
class Button
{
public:
	sf::RectangleShape buttonBG;
	sf::Text buttonText;
	bool bPressed;
	bool bClicked;
	bool bReleased;
	bool bHighlighted;
private:
	sf::Color defaultColour;
	sf::Color highlightedColour;
public:
	Button(sf::Vector2f size, sf::Color colour, const std::string& text);
	~Button() = default;
	bool IsHighlighted()const;
	void Highlight(const sf::RenderWindow* window);
	void Update(const sf::Event event, float );
	void Render(sf::RenderWindow* window, float )const;
	void CheckPressed(sf::Event event);
	
	
};

