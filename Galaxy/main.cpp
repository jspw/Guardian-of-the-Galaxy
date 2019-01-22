#include"Game.h"
#include"GameMapMaker.h"
#include<ctime>
#include <cstdlib>

bool MAPMAKER = false;

int main()
{
	srand(time(NULL));

	bool m = true;

	RenderWindow window(VideoMode(1370, 800), "Gaurdians Of The Galaxy", Style::Default);

	Clock clock;
	float dt = 0.f;

	Game game(&window);
	GameMapMaker gameMapMaker(&window);

	//Song
	Music music;
	music.openFromFile("Sounds/music.wav");
	music.play();


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
		
		if (music.Stopped)
			music.play();

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