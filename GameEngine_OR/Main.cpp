#include "SFML/graphics.hpp"



int main(int argc, char* args[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");
	// Run the program as long as the window is open
	while (window.isOpen() == true)
	{
		sf::Event event;
		while (window.pollEvent(event) == true)
		{
			// Close requested event
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
	return 0;
}