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
	sf::RenderWindow window(sf::VideoMode(1370, 770), "Avengers");
	window.setFramerateLimit(60);

	float shipx = 47, shipy = 331;

	sf::Texture background;
	background.loadFromFile("background.jpg");

	sf::Texture spaceship;
	spaceship.loadFromFile("spaceship.png");
	

	sf::Sprite bk;
	bk.setTexture(background);

	sf::Sprite ss;
	ss.setTexture(spaceship);

	ss.setPosition(sf::Vector2f(shipx, shipy));

	

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			shipy = shipy - 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			shipy = shipy + 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			shipx = shipx - 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			shipx = shipx + 5;

		ss.setPosition(sf::Vector2f(shipx, shipy));
		

		window.clear();
		window.draw(bk);
		window.draw(ss);
		window.display();

	}
}

