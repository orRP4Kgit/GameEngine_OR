#include "Button.h"

Button::Button(sf::Vector2f size, sf::Color colour, const std::string& text) :
    bPressed(false), bClicked(false), bReleased(false), bHighlighted(false), 
    defaultColour(colour), 
    highlightedColour(sf::Color(this->defaultColour.r + 50, this->defaultColour.g + 50, this->defaultColour.b + 50, this->defaultColour.a))
{
    this->buttonBG.setSize(size);
    this->buttonBG.setFillColor(this->defaultColour);
    this->buttonBG.setPosition(0, 0);
    this->buttonText.setCharacterSize(12);
    this->buttonText.setFillColor(sf::Color::White);
    this->buttonText.setPosition(this->buttonBG.getPosition().x / 2, this->buttonBG.getPosition().y / 2);
    this->buttonText.setString(text);
}

bool Button::IsHighlighted()const
{
    return this->bHighlighted;
}

void Button::Highlight(const sf::RenderWindow* window) 
{
    this->bHighlighted = this->buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
    if (this->bHighlighted == true)
    {
        this->buttonBG.setFillColor(this->highlightedColour);
    }
    else
    {
        this->buttonBG.setFillColor(this->defaultColour);
    }
}

void Button::Update(const sf::Event event, float )
{
    this->CheckPressed(event);
}

void Button::Render(sf::RenderWindow* window, float ) const
{
    window->draw(this->buttonBG);
    window->draw(this->buttonText);
    window->display();
}

void Button::CheckPressed(sf::Event event)
{
    if (this->bHighlighted == false)
    {
        return;
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        this->bPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (this->bPressed == false)
        {
            this->bPressed = false;
        }
    }

    if (this->bPressed == true)
    {
        if (event.type = sf::Event::MouseButtonReleased)
        {
            this->bReleased = true;
            this->bClicked = true;
        }
    }
    else
    {
        this->bReleased = false;
        this->bClicked = false;
    }
}
