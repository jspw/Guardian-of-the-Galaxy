#include "Game.h"

Game::Game(RenderWindow *window)
{
	this->window = window;
	this->window->setFramerateLimit(300);
	this->fullscreen = false;
	this->mode = Mode::Survival; //GAME MODE
	this->dtMultiplier = 62.5f;
	this->scoreMultiplier = 1;
	this->score = 0;
	this->scoreTimer.restart();
	this->scoreTime = 0;
	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 200.f;
	this->multiplierTimer = this->multiplierTimerMax;
	this->bestScoreSecond = 0.0;
	this->difficulty = 0;
	this->difficultyTimer = 0.f;

	this->stage = nullptr;

	this->paused = true;
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();
}

Game::~Game()
{
	delete this->stage;
}

void Game::toggleFullscreen()
{
	if (Keyboard::isKeyPressed(Keyboard::F11) && this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;

		if (fullscreen)
		{
			this->fullscreen = false;
			this->window->close();
			this->window->create(sf::VideoMode(1370, 800), "Guardians Of The Galaxy", Style::Default);
		}
		else
		{
			this->fullscreen = true;
			this->window->close();
			this->window->create(sf::VideoMode(1370,800), "Guardians Of The Galaxy", Style::Fullscreen);
		}
	}
}

void Game::pauseGame()
{
	if (Keyboard::isKeyPressed(Keyboard::P) && this->keyTime >= this->keyTimeMax)
	{
		if (this->paused)
			this->paused = false;
		else
			this->paused = true;

		this->keyTime = 0.f;
	}
}

void Game::initRT()
{
	this->mainRenderTexture.create(
		this->window->getSize().x,
		this->window->getSize().y
	);

	this->mainRenderSprite.setTexture(this->mainRenderTexture.getTexture());
}

void Game::initView()
{
	this->mainView.setSize(Vector2f(this->window->getSize()));
	this->mainView.setCenter(Vector2f(
		this->window->getSize().x / 2,
		this->window->getSize().y / 2
	));
}

void Game::initTextures()
{
	//Buttons
	WButton::initTextures();

	//Map
	Stage::initTextures();
	Tile::initTextures();

	//Bullet
	Bullet::initTextures();

	//Player
	Player::initTextures();

	//Pickup
	Pickup::initTextures();

	//Upgrades
	Upgrade::initTextures();

	//Powerup
	Powerup::initTextures();

	//Enemies
	Enemy::initTextures();

	//Bosses

	//Particles
	Particle::initTextures();
}

void Game::initMenues()
{
	//Init main menu
	this->mainMenu.initialize(this->window->getSize());

	//Init in-game menu
}

void Game::initUI()
{
	Text tempText;

	//Follow Text Init
	this->followPlayerText.setFont(font);
	this->followPlayerText.setCharacterSize(14);
	this->followPlayerText.setColor(Color::White);

	//Static Text Init
	this->staticPlayerText.setFont(font);
	this->staticPlayerText.setCharacterSize(14);
	this->staticPlayerText.setColor(Color::White);
	
	//bars init
	this->playerExpBar.setSize(Vector2f(90.f, 10.f));
	this->playerExpBar.setFillColor(Color(0.f, 90.f, 200.f, 200.f));

	this->playerShieldBar.setSize(Vector2f(90.f, 10.f));
	this->playerShieldBar.setFillColor(Color(200.f, 0.f, 100.f, 200.f));

	this->playerPowerupBar.setSize(Vector2f(90.f, 10.f));
	this->playerPowerupBar.setFillColor(Color(0.f, 100.f, 100.f, 200.f));

	//Enemy text init 
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(Color::White);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(this->window->getSize().x/2 - 100.f, this->window->getSize().y / 2);

	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(Color(200,200,200,150));
	this->scoreText.setCharacterSize(32);
	this->scoreText.setString("Score: 0");
	this->scoreText.setPosition(10.f, 10.f);

	this->controlsText.setFont(this->font);
	this->gameOverText.setFillColor(Color::White);
	this->controlsText.setCharacterSize(26);
	this->controlsText.setString(
		"A: LEFT\nD: RIGHT\nW: UP\nS: DOWN\nSPACE: SHOOT\nRALT: SHIELD\nTAB: Stats window\nP: PAUSE/CONTROLS (START GAME)\nESC: QUIT\n1,2,3 & 4: CUSTOMIZE SHIP (CAN DO WHILE PAUSED!)\nF11: FULLSCREEN\n\nTOP-LEFT SHIP: Player number\nTOP-RIGHT SHIP: Hp/HpMax\nBOTTOM-LEFT SHIP: Level\nBOTTOM-RIGHT SHIP: Exp-bar\nBOTTOM-RIGHT SHIP: Shield-bar\n\nWARNING, SCORE-TIMER DOES NOT STOP WHEN PAUSED!"
	);
	this->controlsText.setPosition(50.f, 400.f);

	//PlayerStatText init
	this->playerStatsText.setFont(font);
	this->playerStatsText.setFillColor(Color::White);
	this->playerStatsText.setCharacterSize(16);
	this->playerStatsText.setString("NONE");

	this->playerStatsTextBack.setFillColor(Color(50, 50, 50, 100));
	this->playerStatsTextBack.setOutlineThickness(1.f);
	this->playerStatsTextBack.setOutlineColor(Color(255, 255, 255, 200));
}

void Game::initMap()
{
	this->stage = new Stage(10, 10);
	this->stage->loadStage("lel.wmap", this->mainView);
}

void Game::initialize()
{
	//Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	//INit textures
	this->initTextures();

	//Init menues
	this->initMenues();

	//Init view
	this->initView();

	//Init map
	this->initMap();

	//Init players
	this->players.add(Player());

	//this->players.add(Player(
	//	Keyboard::Numpad8,
	//	Keyboard::Numpad5,
	//	Keyboard::Numpad4,
	//	Keyboard::Numpad6,
	//	Keyboard::RControl,
	//	Keyboard::RShift,
	//	Keyboard::Numpad7,
	//	Keyboard::Numpad1,
	//	Keyboard::Numpad2,
	//	Keyboard::Numpad3,
	//	Keyboard::Numpad0));


	this->Mplayer = true;
	if (Mplayer) {
		this->players.add(Player(
			Keyboard::I,
			Keyboard::K,
			Keyboard::J,
			Keyboard::L,
			Keyboard::RAlt,
			Keyboard::Period,
			Keyboard::Comma,
			Keyboard::Num8,
			Keyboard::Num9,
			Keyboard::Num0,
			Keyboard::Add));
	}

	this->playersAlive = this->players.size();

	//Init enemies

	this->enemySpawnTimerMax = 35.f; //ALSO IN RESET!
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	//Init bosses
	this->bossEncounter = false;

	this->initUI();
}

void Game::updateView(const float &dt)
{
	this->mainView.move(this->stage->getScrollSpeed() * dt * this->dtMultiplier, 0.f);
}

void Game::restartUpdate()
{
	if (Keyboard::isKeyPressed(Keyboard::F1))
	{
		for (size_t i = 0; i < this->players.size(); i++)
		{
			this->players[i].reset();
		}

		this->playersAlive = this->players.size();
		this->score = 0;
		this->scoreMultiplier = 1;
		this->multiplierAdder = 0;
		this->scoreTime = 0;
		this->difficulty = 0;
		this->bossEncounter = false;
		this->enemySpawnTimerMax = 35.f; //ALSO IN CONSTUCTOR!
		this->scoreTimer.restart();
		
		//Reset stage
		this->mainView.setCenter(Vector2f(
			this->window->getSize().x / 2,
			this->window->getSize().y / 2
		));
		this->stage->reset(this->mainView);

		//Clear arrays
		this->enemies.clear();
		this->upgrades.clear();
		this->pickups.clear();
		this->bosses.clear();
		this->powerups.clear();
		this->textTags.clear();
		this->particles.clear();
		
	}
}

void Game::setEndingScoreboard()
{
	this->scoreTime = (int)this->scoreTimer.getElapsedTime().asSeconds();

	if (this->scoreTime == 0)
		this->scoreTime = 1;

	this->gameOverText.setString
	(
		std::string("GAME OVER\nScore: " +
			std::to_string(this->score) +
			"\n" +
			"Time: " +
			std::to_string(this->scoreTime) +
			"\n" +
			"Score/Second: " +
			std::to_string((int)round((double)this->score / (double)this->scoreTime))) +
		"\nF1 to RESTART"
	);

	if ((double)this->score / (double)this->scoreTime > this->bestScoreSecond)
		this->bestScoreSecond = (double)this->score / (double)this->scoreTime;
}

void Game::updateTimers(const float &dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void Game::updateTimersUnpaused(const float &dt)
{
	//Enemy spawn timer
	if (this->enemySpawnTimer < this->enemySpawnTimerMax)
		this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;

	//Difficulty timer
	this->difficultyTimer += 1.f * dt * this->dtMultiplier;

	//Score and multipliers
	if (this->multiplierTimer > 0.f)
	{
		this->multiplierTimer -= 1.f * dt * this->dtMultiplier;

		if (this->multiplierTimer <= 0.f)
		{
			this->multiplierTimer = 0.f;
			this->multiplierAdder = 0;
			this->scoreMultiplier = 1;
		}
	}
}

void Game::updateScore()
{
	if (this->multiplierAdder >= this->multiplierAdderMax)
	{
		this->multiplierAdder = 0;
		this->scoreMultiplier++;
	}
}

void Game::updateDifficulty()
{
	if ((int)this->difficultyTimer % 1000 == 0)
	{
		if(this->enemySpawnTimerMax > 10)
			this->enemySpawnTimerMax--;

		this->difficulty++;
		this->difficultyTimer = 1.f;
	}
}

void Game::updateUIPlayer(int index)
{
	if (index < 0 || index >= this->players.size())
		std::cout << "OUT OF BOUNDS! (UPDATEUI)";

	else //FOLLOW TEXT
	{
		this->followPlayerText.setPosition(
			this->players[index].getPosition().x - 25.f,
			this->players[index].getPosition().y - 68.f
		);

		this->followPlayerText.setString(
			std::to_string(this->players[index].getPlayerNr())
			+ "								"
			+ this->players[index].getHpAsString()
			+ "\n\n\n\n\n\n\n\n\n\n"
			+ std::to_string(this->players[index].getLevel())
		);

		//BARS
		this->playerExpBar.setPosition(
			this->players[index].getPosition().x + 10.f,
			this->players[index].getPosition().y + 115.f
		);

		this->playerExpBar.setScale(
			(static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()),
			1.f
		);

		this->playerShieldBar.setPosition(
			this->players[index].getPosition().x + 10.f,
			this->players[index].getPosition().y + 135.f
		);

		if (this->players[index].getShieldRechargeTimer() < this->players[index].getShieldRechargeTimerMax())
		{
			this->playerShieldBar.setScale(
				(static_cast<float>(this->players[index].getShieldRechargeTimer()) / this->players[index].getShieldRechargeTimerMax()),
				1.f
			);

			if(static_cast<int>(this->players[index].getShieldRechargeTimer()) % 5 == 0)
				this->playerShieldBar.setFillColor(Color::Red);
			else
				this->playerShieldBar.setFillColor(Color(200.f, 200.f, 200.f, 200.f));
		}
		else
		{		
			this->playerShieldBar.setScale(
				(static_cast<float>(this->players[index].getShieldTimer()) / this->players[index].getShieldTimerMax()),
				1.f
			);

			this->playerShieldBar.setFillColor(Color(200.f, 0.f, 100.f, 200.f));
		}

		this->playerPowerupBar.setScale(
			(static_cast<float>(this->players[index].getPowerupTimer()) / this->players[index].getPowerupTimerMax()),
			1.f
		);

		this->playerPowerupBar.setPosition(
			this->players[index].getPosition().x + 10.f,
			this->players[index].getPosition().y + 155.f
		);

		//STATS BOX WITH TEXT
		if (this->players[index].playerShowStatsIsPressed())
		{
			this->playerStatsText.setString(this->players[index].getStatsAsString());

			this->playerStatsTextBack.setPosition(
				this->players[index].getPosition().x, 
				this->players[index].getPosition().y + 150.f
			);
			this->playerStatsTextBack.setSize(Vector2f(this->playerStatsText.getGlobalBounds().width, this->playerStatsText.getGlobalBounds().height));
			
			this->playerStatsText.setPosition(this->playerStatsTextBack.getPosition());
		}
	}
}

void Game::updateUIEnemy(int index)
{
	this->enemyText.setPosition(
		this->enemies[index].getPosition().x,
		this->enemies[index].getPosition().y
		- this->enemies[index].getGlobalBounds().height
	);

	this->enemyText.setString(
		std::to_string(this->enemies[index].getHP()) +
		"/" +
		std::to_string(this->enemies[index].getHPMax()));
}

void Game::updateWhilePaused(const float &dt)
{
	//Change accessories when paused
	if (this->paused)
	{
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				this->players[i].changeAccessories(dt);
			}
		}
	}
}

void Game::playerUpdate(const float &dt)
{
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			//UPDATE PLAYERS
			this->players[i].update(
				this->mainView, 
				dt, 
				stage->getScrollSpeed());

			//Collision update
//			this->playerCollisionUpdate(dt, i);

			//Bullets update
			this->playerBulletUpdate(dt, i);

			//UPDATE SCORE
			this->score = 0;

			for (size_t k = 0; k < this->players.size(); k++)
			{
				this->score += players[k].getScore();
			}

			this->scoreText.setString(
				"Score: " +
				std::to_string(this->score) +
				"\nMultiplier:" +
				std::to_string(this->scoreMultiplier) + "x" +
				"\nMultiplier Timer:" +
				std::to_string((int)this->multiplierTimer) +
				"\nNew Multiplier: " +
				std::to_string(this->multiplierAdder) +
				" / " +
				std::to_string(this->multiplierAdderMax) +
				"\nGame time: " +
				std::to_string((int)this->scoreTimer.getElapsedTime().asSeconds()) +
				"\nDifficulty: " +
				std::to_string(this->difficulty) +
				"\nBest Score/Second: " +
				std::to_string((int)round(this->bestScoreSecond))
			);
		}
	}
}

void Game::playerBulletUpdate(const float &dt, const int i)
{
	bool enemyRemoved = false;
	bool bulletRemoved = false;

	for (size_t k = 0; k < this->players[i].getBulletsSize() && !bulletRemoved; k++)
	{
		this->players[i].getBullet(k).Update(dt);

		//Enemy collision check
		for (size_t j = 0; j < this->enemies.size() && !enemyRemoved; j++)
		{
			if (this->players[i].getBullet(k).getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
			{
				//Enemy take damage
				int damage = this->players[i].getBullet(k).getDamage();
				if (this->enemies[j].getHP() > 0)
				{
					this->enemies[j].takeDamage(damage);

					//Add particles on damage
					int nrOfPart = rand() % 5 + 3;
					for (size_t l = 0; l < nrOfPart; l++)
					{
						this->particles.add(Particle(
							this->players[i].getBullet(k).getPosition(),
							0,
							this->players[i].getBullet(k).getVel(),
							rand() % 20 + 10,
							rand() % 20,
							30.f,
							Color(255, 255, 255, 255)
						));
					}

					//Create text tag
					this->textTags.add(
						TextTag(&this->font,
							"-" + std::to_string(damage),
							Color::Red,
							Vector2f(this->enemies[j].getPosition().x,
								this->enemies[j].getPosition().y - 30.f),
							Vector2f(1.f, 0.f),
							28,
							30.f,
							true
						)
					);
				}

				//Enemy dead
				if (this->enemies[j].getHP() <= 0)
				{
					//Add particles on death
					int nrOfPart = rand() % 30 + 10;
					for (size_t l = 0; l < nrOfPart; l++)
					{
						this->particles.add(Particle(
							this->players[i].getBullet(k).getPosition(),
							0,
							this->players[i].getBullet(k).getVel(),
							rand() % 40 + 10,
							rand() % 20,
							40.f,
							Color(255, 255, 255, 255)
						));
					}

					//GAIN SCORE & RESET MULTIPLIER TIMER
					this->multiplierTimer = this->multiplierTimerMax;
					int score = this->enemies[j].getHPMax() * this->scoreMultiplier;
					this->multiplierAdder++;
					this->players[i].gainScore(score);

					//GAIN EXP
					int exp = this->enemies[j].getHPMax()
						+ (rand() % this->enemies[j].getHPMax() + 1)
						* this->scoreMultiplier;

					if (this->players[i].getPowerupXP())
					{
						exp *= 2;

						//GAIN EXP TAG
						this->textTags.add(
							TextTag(&this->font,
								"+" +
								std::to_string(exp) +
								" ( x" +
								std::to_string(this->scoreMultiplier) +
								" x2 Powerup! ) " +
								" EXP",
								Color::Cyan,
								this->enemies[j].getPosition(),
								Vector2f(1.f, 0.f),
								24,
								40.f,
								true
							)
						);
					}
					else
					{
						//GAIN EXP TAG
						this->textTags.add(
							TextTag(&this->font,
								"+" +
								std::to_string(exp) +
								" ( x" +
								std::to_string(this->scoreMultiplier) +
								" ) " +
								" EXP",
								Color::Cyan,
								this->enemies[j].getPosition(),
								Vector2f(1.f, 0.f),
								24,
								40.f,
								true
							)
						);
					}

					//SCORE TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"+ " + std::to_string(score) +
							"	( x" + std::to_string(this->scoreMultiplier) + " )",
							Color::White,
							Vector2f(100.f, 10.f),
							Vector2f(1.f, 0.f),
							30,
							40.f,
							true
						)
					);

					//LEVEL UP TAG
					if (this->players[i].gainExp(exp))
					{
						this->textTags.add(
							TextTag(&this->font,
								"LEVEL UP!",
								Color::Cyan,
								Vector2f(this->players[i].getPosition().x + 20.f,
									this->players[i].getPosition().y - 20.f),
								Vector2f(0.f, 1.f),
								32,
								40.f,
								true
							)
						);
					}

					//ADD UPGRADE
					int dropChance = rand() % 3;
					int uType = 0;

					switch (dropChance)
					{
					case 0:

						//ADD PICKUP
						dropChance = rand() % 100 + 1;

						if (dropChance > 50)
						{
							this->pickups.add(Pickup(
								this->enemies[j].getPosition(),
								0,
								150.f)
							);
						}

						break;

					case 1:

						//ADD UPGRADE
						dropChance = rand() % 100 + 1;

						if (dropChance > 70)
						{
							uType = rand() % Upgrade::nrOfTextures;

							for (size_t k = 0; k < this->players[i].getAcquiredUpgrades().size(); k++)
							{
								if (uType == this->players[i].getAcquiredUpgrades()[k])
								{
									uType = rand() % 1;
								}
							}

							this->upgrades.add(
								Upgrade
								(
								this->enemies[j].getPosition(),
								uType,
								500.f
								)
							);
						}

						break;

					case 2:

						//ADD Powerup
						dropChance = rand() % 100 + 1;

						if (dropChance > 70)
						{
							uType = rand() % Powerup::nrOfTextures;

							this->powerups.add( 
								Powerup(
									uType,
									300.f,
									this->enemies[j].getPosition()
								)
							);
						}

						break;

					default:
						std::cout << "ERROR NO DROP!" << "\n";
						break;
					}
					
					enemyRemoved = true;	
				}

				//Piercning shot check/Remove bullet
				if (!this->players[i].getPiercingShot())
				{
					bulletRemoved = true;
				}
				else
				{
					this->players[i].getBullet(k).setPosition(
						Vector2f(this->enemies[j].getPosition().x + this->enemies[j].getGlobalBounds().width + this->players[i].getBullet(k).getGlobalBounds().width / 2 + 1.f,
							this->players[i].getBullet(k).getPosition().y)
					);
				}
			}

			if (enemyRemoved)
				this->enemies.remove(j);
		}

		//Window bounds check
		if (this->players[i].getBullet(k).getPosition().x > this->mainView.getCenter().x + this->mainView.getSize().x/2)
		{
			bulletRemoved = true;		
		}

		if(bulletRemoved)
			this->players[i].removeBullet(k);
	}
}

//void Game::playerCollisionUpdate(const float &dt, const int i)
//{
//	//Index calculations
//	if (players[i].isAlive())
//	{
//		this->fromCol = (this->players[i].getPosition().x - Wingman::gridSize*2) / Wingman::gridSize;
//		if (fromCol <= 0)
//			fromCol = 0;
//		if (fromCol >= this->stage->getSizeX())
//			fromCol = this->stage->getSizeX();
//
//		this->toCol = (this->players[i].getPosition().x + Wingman::gridSize * 2) / Wingman::gridSize + 1;
//		if (toCol <= 0)
//			toCol = 0;
//		if (toCol >= this->stage->getSizeX())
//			toCol = this->stage->getSizeX();
//
//		this->fromRow = (this->players[i].getPosition().y - Wingman::gridSize * 2) / Wingman::gridSize;
//		if (fromRow <= 0)
//			fromRow = 0;
//		if (fromRow >= this->stage->getSizeY())
//			fromRow = this->stage->getSizeY();
//
//		this->toRow = (this->players[i].getPosition().y + Wingman::gridSize * 2) / Wingman::gridSize + 1;
//		if (toRow <= 0)
//			toRow = 0;
//		if (toRow >= this->stage->getSizeY())
//			toRow = this->stage->getSizeY();
//
//		for (size_t j = fromCol; j < toCol; j++)
//		{
//			for (size_t k = fromRow; k < toRow; k++)
//			{
//				//Collision
//				if (!this->stage->getTiles()[j].isNull(k)
//					&& this->stage->getTiles()[j][k].getIsCollider()
//					&& this->players[i].getBounds().intersects(this->stage->getTiles()[j][k].getBounds())
//					)
//				{
//					this->players[i].move(-this->players[i].getNormDir().x * 100 * dt * this->dtMultiplier, -this->players[i].getNormDir().y * 100 * dt * this->dtMultiplier);
//					this->players[i].resetVelocity();
//				}
//			}
//		}
//	}
//}

void Game::enemyUpdate(const float &dt)
{
	//Spawn enemies
	this->enemySpawnUpdate(dt);

	//Update enemies
	bool enemyRemoved = false;
	bool playerKilled = false;

	for (size_t i = 0; i < this->enemies.size() && !enemyRemoved; i++)
	{
		this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

		//Enemy player collision
		for (size_t k = 0; k < this->players.size() && !playerKilled; k++)
		{
			if (this->players[k].isAlive())
			{
				if (this->players[k].getBounds().intersects(this->enemies[i].getGlobalBounds())
					&& !this->players[k].isDamageCooldown())
				{
					int damage = this->enemies[i].getDamage();

					//PLAYER TAKES COLLISION DAMAGE
					this->players[k].takeDamage(damage);

					this->enemies[i].collision();

					//PLAYER TAKE DAMAGE TAG
					this->textTags.add(
						TextTag(&this->font,
							"-" + std::to_string(damage),
							Color::Red,
							Vector2f(this->players[k].getPosition().x + 20.f,
								this->players[k].getPosition().y - 20.f),
							Vector2f(-1.f, 0.f),
							30,
							30.f,
							true
						)
					);

					//Player death
					if (!this->players[k].isAlive())
						playerKilled = true;
				}
			}

			if (playerKilled)
				this->playersAlive--;
		}

		//Enemies out of bounds
		if (this->enemies[i].getPosition().x < this->mainView.getCenter().x - this->mainView.getSize().x/2 - this->enemies[i].getGlobalBounds().width)
		{
			enemyRemoved = true;
		}

		if (enemyRemoved)
			this->enemies.remove(i);
	}

	this->enemyBulletUpdate(dt);
}

void Game::enemySpawnUpdate(const float &dt)
{
	//Spawn enemies
	if (this->mode == Mode::Survival)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.add(Enemy(
				this->mainView,
				true,
				Vector2f(0.f, 0.f),
				Vector2f(-1.f, 0.f),
				-1,
				rand() % Enemy::nrOfTypes,
				this->players[(rand() % playersAlive)].getLevel(),
				rand() % this->playersAlive)
			);

			this->enemySpawnTimer = 0; //Reset timer
		}
	}
	else if (this->mode == Mode::Regular)
	{
		//Index calculations
		this->fromCol = (mainView.getCenter().x - mainView.getSize().x / 2) / Galaxy::gridSize;
		if (fromCol <= 0)
			fromCol = 0;
		if (fromCol >= this->stage->getSizeX())
			fromCol = this->stage->getSizeX();

		this->toCol = (mainView.getCenter().x + mainView.getSize().x / 2) / Galaxy::gridSize + 1;
		if (toCol <= 0)
			toCol = 0;
		if (toCol >= this->stage->getSizeX())
			toCol = this->stage->getSizeX();

		this->fromRow = (mainView.getCenter().y - mainView.getSize().y / 2) / Galaxy::gridSize;
		if (fromRow <= 0)
			fromRow = 0;
		if (fromRow >= this->stage->getSizeY())
			fromRow = this->stage->getSizeY();

		this->toRow = (mainView.getCenter().y + mainView.getSize().y / 2) / Galaxy::gridSize + 1;
		if (toRow <= 0)
			toRow = 0;
		if (toRow >= this->stage->getSizeY())
			toRow = this->stage->getSizeY();
		
		for (size_t i = fromCol; i < toCol; i++)
		{
			for (size_t j = fromRow; j < toRow; j++)
			{
				if (!this->stage->getEnemySpawners()[i].isNull(j) 
					&& this->stage->getEnemySpawners()[i][j].getPos().x < this->mainView.getCenter().x + this->mainView.getSize().x / 2
					&& !this->stage->getEnemySpawners()[i][j].isUsed()
					)
					
				{
					int eType = 0;
					int nrOfE = 0;

					if (this->stage->getEnemySpawners()[i][j].getType() < 0)
					{
						eType = rand() % Enemy::nrOfTypes;
					}
					else
						eType = this->stage->getEnemySpawners()[i][j].getType();

					if (this->stage->getEnemySpawners()[i][j].getNrOfEnemies() < 0)
					{
						nrOfE = rand() % 10 + 1;
					}
					else
						nrOfE = this->stage->getEnemySpawners()[i][j].getNrOfEnemies();
					
					for (size_t k = 0; k < nrOfE; k++)
					{
						std::cout << eType << "\n" << this->players[(rand() % playersAlive)].getLevel() << "\n";
						this->enemies.add(Enemy(
							this->mainView,
							this->stage->getEnemySpawners()[i][j].getRandomSpawnPos(),
							this->stage->getEnemySpawners()[i][j].getPos(),
							Vector2f(-1.f, 0.f),
							this->stage->getEnemySpawners()[i][j].getMaxVelocity(),
							eType,
							this->players[(rand() % playersAlive)].getLevel(),
							rand() % this->playersAlive)
						);

						this->stage->getEnemySpawners()[i][j].setUsed();
				
					}	
				}
			}
		}
	}	
}

void Game::enemyBulletUpdate(const float &dt)
{
	//Enemy bullet update
	bool bulletRemoved = false;
	bool playerKilled = false;
	for (size_t i = 0; i < Enemy::enemyBullets.size() && !bulletRemoved; i++)
	{
		Enemy::enemyBullets[i].Update(dt);

		//Player collision check
		for (size_t k = 0; k < this->players.size() && !playerKilled; k++)
		{
			if (Enemy::enemyBullets[i].getGlobalBounds().intersects(this->players[k].getBounds())
				&& this->players[k].isAlive())
			{
				int damage = Enemy::enemyBullets[i].getDamage();

				//PLAYER TAKES BULLET DAMAGE
				if (!this->players[k].isShielding())
				{
					this->players[k].takeDamage(damage);

					//PLAYER TAKE DAMAGE TAG
					this->textTags.add(
						TextTag(&this->font,
							"-" + std::to_string(damage),
							Color::Red,
							Vector2f(this->players[k].getPosition().x + 20.f,
								this->players[k].getPosition().y - 20.f),
							Vector2f(-1.f, 0.f),
							30,
							30.f,
							true
						)
					);

					//Player death
					if (!this->players[k].isAlive())
						playerKilled = true;
				}
				else
				{
					//Add particles on shielding
					int nrOfPart = rand() % 5 + 3;
					for (size_t l = 0; l < nrOfPart; l++)
					{
						this->particles.add(Particle(
							Enemy::enemyBullets[i].getPosition(),
							0,
							Enemy::enemyBullets[i].getVel(),
							rand() % 20 + 5,
							rand() % 20,
							30.f,
							Color(0, 50, 255, 255)
						));
					}

					//PLAYER SHIELDED TAG
					this->textTags.add(
						TextTag(&this->font,
							"-" + std::to_string(0),
							Color::Cyan,
							Vector2f(this->players[k].getPosition().x + 20.f,
								this->players[k].getPosition().y - 20.f),
							Vector2f(-1.f, 0.f),
							30,
							30.f,
							true
						)
					);
				}

				bulletRemoved = true;
			}

			if (playerKilled)
				this->playersAlive--;
		}

		//Window bounds check
		if (!bulletRemoved
			&& (Enemy::enemyBullets[i].getPosition().x > this->mainView.getCenter().x + this->mainView.getSize().x/2
				|| Enemy::enemyBullets[i].getPosition().x < this->mainView.getCenter().x - this->mainView.getSize().x / 2
				|| Enemy::enemyBullets[i].getPosition().y > this->mainView.getCenter().y + this->mainView.getSize().y / 2
				|| Enemy::enemyBullets[i].getPosition().y < this->mainView.getCenter().y - this->mainView.getSize().y / 2
				))
		{
			bulletRemoved = true;
		}

		if (bulletRemoved)
			Enemy::enemyBullets.remove(i);
	}
}

void Game::textTagsUpdate(const float &dt)
{
	bool textTagRemoved = false;
	for (size_t i = 0; i < this->textTags.size() && !textTagRemoved; i++)
	{
		this->textTags[i].Update(dt);

		if (this->textTags[i].getTimer() <= 0.f)
		{
			textTagRemoved = true;
		}

		if (textTagRemoved)
			this->textTags.remove(i);
	}
}

void Game::pickupsUpdate(const float &dt)
{
	bool pickupRemoved = false;
	for (size_t i = 0; i < this->pickups.size() && !pickupRemoved; i++)
	{
		this->pickups[i].Update(dt);

		for (size_t k = 0; k < this->players.size(); k++)
		{
			if (this->players[k].isAlive() && this->pickups[i].checkCollision(this->players[k].getBounds()))
			{
				int gainHp = this->players[k].getHpMax() / 5;

				switch (this->pickups[i].getType())
				{
				case 0: //HP

					if (this->players[k].getHp() < this->players[k].getHpMax())
					{
						this->players[k].gainHP(gainHp);

						//GAIN HP TAG
						this->textTags.add(
							TextTag(&this->font,
								"+" +
								std::to_string(gainHp) +
								" HP",
								Color::Green,
								Vector2f(this->players[k].getPosition()),
								Vector2f(0.f, -1.f),
								24,
								40.f,
								true
							)
						);
					}
					else
					{
						//GAIN EXP TAG
						this->textTags.add(
							TextTag(&this->font,
								"+" +
								std::to_string(10) +
								" EXP",
								Color::Cyan,
								this->pickups[i].getPosition(),
								Vector2f(1.f, 0.f),
								24,
								40.f,
								true
							)
						);
						if (this->players[k].gainExp(10))
						{
							this->textTags.add(
								TextTag(&this->font,
									"LEVEL UP!",
									Color::Cyan,
									Vector2f(this->players[i].getPosition().x + 20.f,
										this->players[i].getPosition().y - 20.f),
									Vector2f(0.f, 1.f),
									32,
									40.f,
									true
								)
							);
						}
					}
					break;

				case 1: //MISSILE

					break;

				case 2: //HMISSILE

					break;

				default:

					break;
				}

				pickupRemoved = true;
			}
		}
		if (this->pickups[i].canDelete())
		{
			pickupRemoved = true;
		}

		if (pickupRemoved)
			this->pickups.remove(i);
	}
}

void Game::upgradesUpdate(const float &dt)
{
	bool upgradeRemoved = false;
	bool hasUpgrade = false;

	for (size_t i = 0; i < this->upgrades.size() && !upgradeRemoved; i++)
	{
		this->upgrades[i].Update(dt);

		for (size_t k = 0; k < this->players.size(); k++)
		{
			if (this->players[k].isAlive() && this->upgrades[i].checkCollision(this->players[k].getBounds()))
			{
				if (this->upgrades[i].getType() != 0 && this->upgrades[i].getType() != 1)
				{
					for (size_t j = 0; j < this->players[k].getAcquiredUpgrades().size() && !hasUpgrade; j++)
					{
						if (this->upgrades[i].getType() == this->players[k].getAcquiredUpgrades()[j])
							hasUpgrade = true;
					}

					if(!hasUpgrade)
						this->players[k].getAcquiredUpgrades().add(this->upgrades[i].getType());
				}

				switch (this->upgrades[i].getType())
				{

				case Upgrade::STAT_POINT: //Statpoint

					this->players[k].addStatPointRandom();

					//HT TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"RANDOM STATPOINT UPGRADE",
							Color::Yellow,
							this->players[k].getPosition(),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);

					break;

				case Upgrade::HEALTH_TANK: //Healthtank
					this->players[k].upgradeHP();

					//HT TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"PERMANENT HEALTH UPGRADE",
							Color::Yellow,
							this->players[k].getPosition(),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);

					break;

				case Upgrade::DOUBLE_RAY: //Doubleray
					if (this->players[k].getGunLevel() < 1)
						this->players[k].setGunLevel(1);

					//DR TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"DOUBLE RAY UPGRADE",
							Color::Yellow,
							this->players[k].getPosition(),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);

					break;

				case Upgrade::TRIPLE_RAY: //Tripleray
					if (this->players[k].getGunLevel() < 2)
						this->players[k].setGunLevel(2);

					//TR TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"TRIPLE RAY UPGRADE",
							Color::Yellow,
							this->players[k].getPosition(),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);

					break;

				case Upgrade::PIERCING_SHOT: //Piercing
					this->players[k].enablePiercingShot();

					//PS TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"PIERCING SHOT UPGRADE",
							Color::Yellow,
							this->players[k].getPosition(),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);

					break;

				case Upgrade::SHIELD: //Shield
					this->players[k].enableShield();

					//SH TEXT TAG
					this->textTags.add(
						TextTag(&this->font,
							"SHIELD UPGRADE",
							Color::Yellow,
							this->players[k].getPosition(),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);

					break;

				default:
					break;
				}

				upgradeRemoved = true;
			}
		}

		if (this->upgrades[i].canDelete())
		{
			upgradeRemoved = true;
		}

		if (upgradeRemoved)
			this->upgrades.remove(i);
	}
}

void Game::powerupsUpdate(const float &dt)
{
	bool powerupRemoved = false;
	for (size_t i = 0; i < this->powerups.size(); i++)
	{
		this->powerups[i].update(dt);

		for (size_t k = 0; k < this->players.size(); k++)
		{
			if (this->players[k].isAlive() && this->powerups[i].collide(this->players[k].getBounds()))
			{
				switch (this->powerups[i].getType())
				{
				case 0: //RF
					this->players[k].enablePowerupRF();

					break;

				case 1: //XP
					this->players[k].enablePowerupXP();

					break;

				default:
					break;
				}

				powerupRemoved = true;
			}
		}
		
		if (this->powerups[i].canRemove())
			powerupRemoved = true;

		if (powerupRemoved)
			this->powerups.remove(i);
	}
}

void Game::mapUpdate(const float &dt)
{
	this->stage->update(dt, this->mainView, false);
}

void Game::particlesUpdate(const float &dt)
{
	bool particleRemoved = false;
	for (size_t i = 0; i < this->particles.size() && !particleRemoved; i++)
	{
		this->particles[i].update(dt);

		if (this->particles[i].readyToDel())
			particleRemoved = true;

		if(particleRemoved)
			this->particles.remove(i);
	}
}

void Game::update(const float &dt)
{	
	//Timers UPDATE
	this->updateTimers(dt);

	//Fullscreen
	this->toggleFullscreen();

	//PAUSE GAME
	this->pauseGame();

	//Update while game paused
	this->updateWhilePaused(dt);

	//GAME START
	if (this->playersAlive > 0 && !this->paused)
	{
		//Update timers
		this->updateTimersUnpaused(dt);

		//View
		this->updateView(dt);

		//MAKE GAME HARDER WITH TIME
		this->updateDifficulty();

		//Score timer and multipliers
		this->updateScore();
		
		//Map update
		this->mapUpdate(dt);

		//Update players, bullets and combat
		this->playerUpdate(dt);

		//Update enemies
		this->enemyUpdate(dt);

		//Update Texttags
		this->textTagsUpdate(dt);

		//Upgrades update
		this->upgradesUpdate(dt);

		//Pickups update
		this->pickupsUpdate(dt);

		//Powerups update
		this->powerupsUpdate(dt);

		//Particles
		this->particlesUpdate(dt);

		//Restart
		this->restartUpdate();
	}
	else if(this->playersAlive <= 0 && this->scoreTime == 0)
	{
		this->setEndingScoreboard(); //Best score is set
	}
	
	//Restart if all players dead
	if (this->playersAlive <= 0)
	{
		this->restartUpdate();
	}
}

void Game::drawUI()
{
	//GAME OVER TEXT
	if (this->playersAlive <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	//Score text
	this->window->draw(this->scoreText);

	//CONTROLS TEXT
	if (this->paused)
		this->window->draw(this->controlsText);
}

void Game::drawPlayers()
{
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			this->players[i].draw(*this->window);

			//UI
			this->updateUIPlayer(i);

			this->window->draw(this->followPlayerText);
			this->window->draw(this->playerExpBar);
			this->window->draw(this->playerShieldBar);
			this->window->draw(this->playerPowerupBar);

			if (this->players[i].playerShowStatsIsPressed())
			{
				this->window->draw(this->playerStatsTextBack);
				this->window->draw(this->playerStatsText);
			}
		}
	}
}

void Game::drawEnemies()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);

		//UI
		this->updateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	//enemy bullets
	for (size_t i = 0; i < Enemy::enemyBullets.size(); i++)
	{
		Enemy::enemyBullets[i].Draw(*this->window);
	}
}

void Game::drawMap()
{
	stage->draw(
		*this->window, 
		this->mainView,
		false,
		this->font
	);
}

void Game::drawTextTags()
{
	//Draw texttags
	for (size_t i = 0; i < this->textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}
}

void Game::drawPickups()
{
	for (size_t i = 0; i < this->pickups.size(); i++)
	{
		this->pickups[i].Draw(*this->window);
	}
}

void Game::drawUpgrades()
{
	for (size_t i = 0; i < this->upgrades.size(); i++)
	{
		this->upgrades[i].Draw(*this->window);
	}
}

void Game::drawPowerups()
{
	for (size_t i = 0; i < this->powerups.size(); i++)
	{
		this->powerups[i].draw(*this->window);
	}
}

void Game::drawParticles()
{
	for (size_t i = 0; i < this->particles.size(); i++)
	{
		this->particles[i].draw(*this->window);
	}
}

void Game::draw()
{
	//CLEAR AND BEGIN DRAW
	this->window->clear();

	//Set view
	this->window->setView(this->mainView);

	//Draw map
	this->drawMap();

	//Draw playerspdssdwds
	this->drawPlayers();

	//Draw enemies
	this->drawEnemies();

	//Draw pickups
	this->drawPickups();

	//Draw Upgrades
	this->drawUpgrades();

	//Draw Powerups
	this->drawPowerups();

	//Draw Particles
	this->drawParticles();

	//Draw Texttags
	this->drawTextTags();

	//Draw UI

	//Set view
	this->window->setView(this->window->getDefaultView());

	this->drawUI();

	//FINISH DRAW
	this->window->display();
}



/*
PROPERTY Of Mehedi Hasan Shifat.
No third party has the rights to sell or distribute this software and all its files and source-code.
No third party has the right to copy this software and all it's components for uses other than personal learning and testing.
*/