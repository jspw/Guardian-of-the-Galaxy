#include"Game.h"
#include"GameMapMaker.h"
#include<ctime>
#include <cstdlib>

bool MAPMAKER = false;

int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(1370, 800), "Gaurdians Of The Galaxy", Style::Default);

	Clock clock;
	float dt = 0.f;

	Game game(&window);
	GameMapMaker gameMapMaker(&window);

	//Song
	sf::SoundBuffer buffer;
	// load something into the sound buffer...
	buffer.loadFromFile("music.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	//fireSound
	sf::SoundBuffer buffer2;
	// load something into the sound buffer...
	buffer2.loadFromFile("Sounds/fire.wav");
	sf::Sound fireSound;
	fireSound.setBuffer(buffer2);
	



	//Game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();		
		}

		dt = clock.restart().asSeconds();
		sound.play();

		if (MAPMAKER)
		{
			gameMapMaker.update(dt);
			gameMapMaker.draw();
		}
		else
		{
			game.update(dt);
			game.draw();
		}
	}

	return 0;
}