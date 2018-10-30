#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\System.hpp"
#include "SFML\Network.hpp"
#include <SFML/OpenGL.hpp>
#include<iostream>

using namespace sf;
int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Avengers");
	window.setFramerateLimit(60);
	sf::Texture background;
	background.loadFromFile("background.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();

	}
}

