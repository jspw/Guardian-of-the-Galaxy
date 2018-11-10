#include "pch.h"
#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<math.h>
#include<cstdlib>
#include<vector>

using namespace sf;

//VECTOR MATH
//LENGTH OF VECTOR
//|V| = sqrt(pow(2, Vx) + pow(2, Vy));
//NORMALIZE
//U = V/|V| = (Vx, Vy) / sqrt(pow(2, Vx) + pow(2, Vy));

class Bullet
{
public:
	Sprite shape;

	Bullet(Texture *texture, Vector2f pos)
	{
		this->shape.setTexture(*texture);

		this->shape.setScale(0.03f, 0.03f);

		this->shape.setPosition(pos);
	}

	~Bullet() {}
};

class Ebullet
{
public:
	Sprite shape;

	Ebullet(Texture *texture, Vector2f pos)
	{
		this->shape.setTexture(*texture);

		//	this->shape.setScale(0.03f, 0.03f);

		this->shape.setPosition(pos);
	}

	~Ebullet() {}
};

class Player
{
public:
	Sprite shape;
	Texture *texture;

	int HP;
	int HPMax;

	std::vector<Bullet> bullets;

	Player(Texture *texture)
	{
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture);
		this->shape.setPosition(37, 345);
		//	this->shape.setScale(0.1f, 0.1f);
	}

	~Player() {}

};

class Enemy
{
public:
	Sprite shape;

	int HP;
	int HPMax;


	Enemy(Texture *texture, Vector2u windowSize)
	{
		this->HPMax = rand() % 3 + 1;
		this->HP = this->HPMax;

		this->shape.setTexture(*texture);

		this->shape.setScale(0.3f, 0.3f);

		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
	}

	~Enemy() {}
};

class XEnemy
{
public:
	Sprite shape;
	Texture *texture;
	int HP;
	int HPMax;

	std::vector<Ebullet> ebullets;

	XEnemy(Texture *texture)
	{
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture);

		//	this->shape.setScale(0.1f, 0.1f);
		this->shape.setPosition(1200,rand()%700);
	}

	~XEnemy() {}

};

class Particles
{
public:
	Sprite shape;

	Particles(Texture *texture, Vector2u windowSize)
	{


		this->shape.setTexture(*texture);

		//	this->shape.setScale(0.1f, 0.1f);

		this->shape.setPosition(rand() % windowSize.x, rand() % windowSize.y);
	}

	~Particles() {}
};

class Particlesx
{
public:
	Sprite shape;

	Particlesx(Texture *texture, Vector2u windowSize)
	{


		this->shape.setTexture(*texture);

		//	this->shape.setScale(0.1f, 0.1f);

		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
	}

	~Particlesx() {}
};

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1365, 767), "Gaurdians of The Galaxy");
	window.setFramerateLimit(60);

	bool flameb = false;
	bool explotionb = false;
	int xenemyY = 323;



	//load background
	sf::Texture background1;
	background1.loadFromFile("background1.jpg");
	sf::Sprite bk1;
	bk1.setTexture(background1);

	//load earth
	sf::Texture er;
	er.loadFromFile("planet_earth.png");
	sf::Sprite earth;
	earth.setTexture(er);
	earth.setPosition(Vector2f(500, 200));

	//asteroids
	sf::Texture as1;
	as1.loadFromFile("asteroid1.png");
	sf::Sprite asteroid1;
	asteroid1.setTexture(as1);

	sf::Texture as2;
	as2.loadFromFile("asteroid2.png");
	sf::Sprite asteroid2;
	asteroid2.setTexture(as2);

	sf::Texture as3;
	as3.loadFromFile("asteroid3.png");
	sf::Sprite asteroid3;
	asteroid3.setTexture(as3);

	sf::Texture as4;
	as4.loadFromFile("asteroid4.png");
	sf::Sprite asteroid4;
	asteroid4.setTexture(as4);

	asteroid1.setPosition(Vector2f(1365, rand() % window.getSize().y));
	asteroid2.setPosition(Vector2f(1365, rand() % window.getSize().y));
	asteroid3.setPosition(Vector2f(1365, rand() % window.getSize().y));
	asteroid4.setPosition(Vector2f(1365, rand() % window.getSize().y));


	//load flame
	sf::Texture fl;
	fl.loadFromFile("flame.png");
	sf::Sprite flame;
	flame.setTexture(fl);

	//load particle
	sf::Texture par1;
	par1.loadFromFile("particle1.png");
	sf::Sprite particle1;
	particle1.setTexture(par1);
	particle1.setPosition(Vector2f(1370, 100));

	//Explotion
	sf::Texture expl;
	expl.loadFromFile("explotion.png");
	sf::Sprite explotion;
	explotion.setTexture(expl);





	sf::SoundBuffer buffer;
	// load something into the sound buffer...
	buffer.loadFromFile("music.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);


	//fireSound
	sf::SoundBuffer buffer2;
	// load something into the sound buffer...
	buffer2.loadFromFile("fire.wav");
	sf::Sound fireSound;
	fireSound.setBuffer(buffer2);

	//Init text
	Font font;
	font.loadFromFile("JANCIENT.TTF");

	//Init textures
	Texture playerTex;
	playerTex.loadFromFile("spacecraft1.png");

	Texture enemyTex;
	enemyTex.loadFromFile("RD2.png");

	Texture bulletTex;
	bulletTex.loadFromFile("missileTex01.png");

	Texture ebulletTex;
	ebulletTex.loadFromFile("Ebullet.png");

	sf::Texture par2;
	par2.loadFromFile("litleParticle.png");

	sf::Texture par3;
	par3.loadFromFile("litleParticle.png");

	sf::Texture XenemyTex;
	XenemyTex.loadFromFile("xenemy.png");

	//UI init
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(100.f, window.getSize().y / 2);
	gameOverText.setString("GAME OVER!");

	//Player init
	int score = 0;
	Player player(&playerTex);
	int shootTimer = 20;
	Text hpText;
	hpText.setFont(font);
	hpText.setCharacterSize(12);
	hpText.setFillColor(Color::White);

	//Enemy init
	int enemySpawnTimer = 0;
	std::vector<Enemy> enemies;



	//Xenemy init

	XEnemy xenemy(&XenemyTex);
	int eshootTimer = 20;

	hpText.setFont(font);
	hpText.setCharacterSize(12);
	hpText.setFillColor(Color::Red);



	//particles init
	int particlesSpawnTimer = 0;
	std::vector<Particles> particles;

	int particlesSpawnTimerb = 0;
	std::vector<Particlesx> particlesx;

	Text eHpText;
	eHpText.setFont(font);
	eHpText.setCharacterSize(12);
	eHpText.setFillColor(Color::White);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (player.HP > 0)
		{
			//Player
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.shape.move(0.f, -10.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.shape.move(-10.f, 0.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.shape.move(0.f, 10.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player.shape.move(10.f, 0.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				player.shape.move(0.f, -10.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				player.shape.move(-10.f, 0.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				player.shape.move(0.f, 10.f);
				flameb = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				player.shape.move(10.f, 0.f);
				flameb = true;
			}

			hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
			hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));


			//flame
			float  flamex = player.shape.getPosition().x - 7;
			float flamey = player.shape.getPosition().y + 7;
			flame.setPosition(sf::Vector2f(flamex, flamey));


			//particles

			particle1.setPosition(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));

			//asteroid
					//move
			asteroid1.move(-3.f, 0);
			asteroid1.setRotation(180);
			asteroid2.move(-4.f, 0);
			asteroid2.setRotation(180);
			asteroid3.move(-2.f, 0);
			asteroid3.setRotation(180);
			asteroid4.move(-1.f, 0);
			asteroid4.setRotation(180);


			if (asteroid1.getPosition().x < 0) {
				asteroid1.setPosition(Vector2f(1365, rand() % window.getSize().y));
			}

			if (asteroid2.getPosition().x < 0) {
				asteroid2.setPosition(Vector2f(1365, rand() % window.getSize().y));
			}
			if (asteroid3.getPosition().x < 0) {
				asteroid3.setPosition(Vector2f(1365, rand() % window.getSize().y));
			}
			if (asteroid4.getPosition().x < 0) {
				asteroid4.setPosition(Vector2f(1365, rand() % window.getSize().y));
			}

			//Collision with window
			if (player.shape.getPosition().x <= 0) //Left
				player.shape.setPosition(0.f, player.shape.getPosition().y);
			if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
				player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
			if (player.shape.getPosition().y <= 0) //Top
				player.shape.setPosition(player.shape.getPosition().x, 0.f);
			if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
				player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

			//Update Controls

			

			//xenemy
			xenemy.shape.setPosition(1200, xenemyY);
			xenemyY=xenemyY+5;
			if (xenemyY > 767)
				xenemyY = 0;

			//Enemy
			if (enemySpawnTimer < 50)
				enemySpawnTimer++;

			//enemy spawn
			if (enemySpawnTimer >= 50)
			{
				enemies.push_back(Enemy(&enemyTex, window.getSize()));
				enemySpawnTimer = 0; //reset timer
			}

			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(-5.f, 0.f);

				if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
				{
					enemies.erase(enemies.begin() + i);
					break;
				}

				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + i);

					player.HP--; // PLAYER TAKE DAMAGE
					break;
				}
			}

			//shooting
			//bullets
			if (shootTimer < 15)
				shootTimer++;

			if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 15) //Shooting
			{
				player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
				shootTimer = 0; //reset timer
				fireSound.play();
				flameb = true;
			}


			//shooting
			//enemy bullets
			if (eshootTimer < 20)
				eshootTimer++;

			if (eshootTimer >= 20 ) //Shooting
			{
				xenemy.ebullets.push_back(Ebullet(&ebulletTex, xenemy.shape.getPosition()));
				eshootTimer = 0; //reset timer
			//	efireSound.play();
			}



			//Bullets
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				//Move
				player.bullets[i].shape.move(10.f, 0.f);

				//Out of window bounds
				if (player.bullets[i].shape.getPosition().x > window.getSize().x)
				{
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}

				//Enemy collision && asteroids
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
					{
						if (enemies[k].HP <= 1)
						{
							score += enemies[k].HPMax;
							enemies.erase(enemies.begin() + k);
						}
						else {
							enemies[k].HP--; //ENEMY TAKE DAMAGE
							explotionb = true;

						}

						player.bullets.erase(player.bullets.begin() + i);
						break;
					}

					if (player.bullets[i].shape.getGlobalBounds().intersects(asteroid1.getGlobalBounds())) {
						asteroid1.setPosition(Vector2f(1365, rand() % window.getSize().y));
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
					if (player.bullets[i].shape.getGlobalBounds().intersects(asteroid2.getGlobalBounds())) {
						asteroid2.setPosition(Vector2f(1365, rand() % window.getSize().y));
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
					if (player.bullets[i].shape.getGlobalBounds().intersects(asteroid3.getGlobalBounds())) {
						asteroid3.setPosition(Vector2f(1365, rand() % window.getSize().y));
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
					if (player.bullets[i].shape.getGlobalBounds().intersects(asteroid4.getGlobalBounds())) {
						asteroid4.setPosition(Vector2f(1365, rand() % window.getSize().y));
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}


					//xenemy collition
					if (player.bullets[i].shape.getGlobalBounds().intersects(xenemy.shape.getGlobalBounds())) {
						xenemy.HP--;
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
				}
			}


			//enemy Bullets
			for (size_t i = 0; i < xenemy.ebullets.size(); i++)
			{
				//Move
				xenemy.ebullets[i].shape.move(-6.f, 0.f);

				//Out of window bounds
				if (xenemy.ebullets[i].shape.getPosition().x > window.getSize().x)
				{
					xenemy.ebullets.erase(xenemy.ebullets.begin() + i);
					break;
				}

				//Enemy collision

				if (xenemy.ebullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{

					player.HP--; //player TAKE DAMAGE
					explotionb = true;

					xenemy.ebullets.erase(xenemy.ebullets.begin() + i);
					break;

				}


			}

			//Particls
			if (particlesSpawnTimer < 5)
				particlesSpawnTimer++;

			//Particles spawn
			if (particlesSpawnTimer >= 5)
			{
				particles.push_back(Particles(&par2, window.getSize()));
				particlesSpawnTimer = 0; //reset timer
			}

			for (size_t i = 0; i < particles.size(); i++)
			{
				particles[i].shape.move(6.f, 0.f);

				if (particles[i].shape.getPosition().x <= 0 - particles[i].shape.getGlobalBounds().width)
				{
					particles.erase(particles.begin() + i);
					break;
				}
			}

			//Particlsx
			if (particlesSpawnTimerb < 3)
				particlesSpawnTimerb++;

			//Particlesx spawn
			if (particlesSpawnTimerb >= 3)
			{
				particlesx.push_back(Particlesx(&par2, window.getSize()));
				particlesSpawnTimerb = 0; //reset timer
			}

			for (size_t i = 0; i < particlesx.size(); i++)
			{
				particlesx[i].shape.move(-10.f, 0.f);

				if (particlesx[i].shape.getPosition().x <= 0 - particlesx[i].shape.getGlobalBounds().width)
				{
					particlesx.erase(particlesx.begin() + i);
					break;
				}
			}

			//UI Update
			scoreText.setString("Score: " + std::to_string(score));
		}

		//Draw =========================== DRAW
		window.clear();
		window.draw(bk1);
		window.draw(particle1);


		window.draw(earth);

		if (flameb)
			window.draw(flame);

		window.draw(asteroid1);
		window.draw(asteroid2);
		window.draw(asteroid3);
		window.draw(asteroid4);

		//player
		window.draw(player.shape);

		//Bullets
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}

		//enemy Bullets
		if (xenemy.HP > 1) {
			for (size_t i = 0; i < xenemy.ebullets.size(); i++)
			{
				window.draw(xenemy.ebullets[i].shape);
			}
		}

		//enemy
		for (size_t i = 0; i < enemies.size(); i++)
		{
			eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
			eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
			window.draw(eHpText);
			window.draw(enemies[i].shape);
		}
		//xenmey
		if(xenemy.HP>1)
		window.draw(xenemy.shape);

		//particles
		for (size_t i = 0; i < particles.size(); i++)
		{

			window.draw(particles[i].shape);
		}

		//particlesx
		for (size_t i = 0; i < particlesx.size(); i++)
		{

			window.draw(particlesx[i].shape);
		}

		//UI



		window.draw(scoreText);
		window.draw(hpText);

		if (player.HP <= 0)
			window.draw(gameOverText);

		window.display();
		flameb = false;
		explotionb = false;
	}

	return 0;
}
