#include "GameMapMaker.h"

GameMapMaker::GameMapMaker(RenderWindow *window)
{
	this->window = window;
	this->window->setFramerateLimit(300);
	this->fullscreen = false;
	this->toolSelect = Stage::tileType::regularTile;
	this->dtMultiplier = 62.5f;
	this->backgroundIndex = 0;
	this->backgroundWidth = Galaxy::backgroundSize;
	this->backgroundHeight = Galaxy::backgroundSize;

	//Variables for tiles
	this->tileCollider = false;

	//Variables for enemySpawner
	this->enemyRandomSpawnPos = false;
	this->enemyMaxVelocity = 0;
	enemyType = 0;
	enemyLevelInterval = 0;
	nrOfEnemies = 0;

	this->stage = nullptr;

	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();
}

GameMapMaker::~GameMapMaker()
{
	delete this->stage;
}

void GameMapMaker::toggleFullscreen()
{
	if (Keyboard::isKeyPressed(Keyboard::F11) && this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;

		if (fullscreen)
		{
			this->fullscreen = false;
			this->window->close();
			this->window->create(sf::VideoMode(1920, 1080), "Wingman GameMapMaker", Style::Default);
		}
		else
		{
			this->fullscreen = true;
			this->window->close();
			this->window->create(sf::VideoMode(1920, 1080), "Wingman GameMapMaker", Style::Fullscreen);
		}
	}
}

void GameMapMaker::newStage()
{
	unsigned mapSizeX = 0;
	unsigned mapSizeY = 0;

 	std::cout << "New Map" << "\n\n";
	
	std::cout << "Map name:";
	std::getline(std::cin, this->stageName);
	this->stageName.append(".wmap");

	std::cout << "Map size X: ";
	std::cin >> mapSizeX;

	while (std::cin.fail() || mapSizeX <= 0)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Map size X: " << "\n";
		std::cin >> mapSizeX;
	}

	std::cout << "Map size Y: ";
	std::cin >> mapSizeY;

	while (std::cin.fail() || mapSizeY <= 0)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Map size Y: " << "\n";
		std::cin >> mapSizeY;
	}

	std::cin.ignore(100, '\n');
	std::cout << "\n";

	delete this->stage;
	this->stage = new Stage(mapSizeX, mapSizeY);

	std::cout << "Stage " << this->stageName << " created!" << "\n\n";
}

void GameMapMaker::saveStage()
{
	std::cout << "Save Stage" << "\n\n";

	std::ifstream in;
	int choice = 0;

	in.open(this->stageName);

	if (in.is_open()) //File already exists
	{
		std::cout << "File " << this->stageName << " already exists! Overwrite? (0) NO (1) YES) \n\n";

		std::cout << "Choice: ";
		
		std::cin >> choice;

		while (std::cin.fail() || choice > 1)
		{
			std::cout << "Faulty input!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "Choice (0) NO (1) YES: " << "\n";
			std::cin >> choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		if (choice == 0)
		{
			std::cout << "Did not overwrite!" << "\n\n";
		}
		else
		{
			this->stage->saveStage(this->stageName);
			std::cout << "Stage " << this->stageName << " saved and overwritten!" << "\n\n";
		}
	}
	else //Save
	{
		this->stage->saveStage(this->stageName);
		std::cout << "Stage " << this->stageName << " saved!" << "\n\n";
	}
	
	in.close();
}

void GameMapMaker::loadStage()
{
	std::cout << "Load Stage" << "\n\n";

	std::string fileName = "";

	std::cout << "File name (without extension!): ";
	std::getline(std::cin, fileName);
	fileName.append(".wmap");

	if (this->stage->loadStage(fileName, this->mainView))
	{
		this->stageName = fileName;
		std::cout << fileName << " Loaded!" << "\n\n";
	}
	else
	{
		std::cout << "Could not load " << fileName << "!" << "\n\n";
	}
}

void GameMapMaker::setBackground()
{
	int choice = 0;
	
	std::cout << "Background select" << "\n";
	
	std::cout << "Background index(" << "0 - " << Stage::nrOfBackgrounds << ")";
	std::cin >> choice;

	while (std::cin.fail() || choice >= Stage::nrOfBackgrounds)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Background index(" << "0 - " << Stage::nrOfBackgrounds << ")";
		std::cin >> choice;
	}

	if (choice >= 0)
	{
		this->backgroundIndex = choice;
	}
	else
		std::cout << "NO BACKGROUND SELECTED!" << "\n\n";

	std::cout << "Background Size X";
	std::cin >> choice;

	while (std::cin.fail() || choice < Galaxy::backgroundSize)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Background Size X";
		std::cin >> choice;
	}
	
	this->backgroundWidth = choice;

	std::cout << "Background Size Y";
	std::cin >> choice;

	while (std::cin.fail() || choice < Galaxy::backgroundSize)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Background Size Y";
		std::cin >> choice;
	}

	this->backgroundHeight = choice;

	this->stage->setBackground(this->backgroundIndex, this->backgroundWidth, this->backgroundHeight);

	std::cin.ignore(100, '\n');
	std::cout << "\n";
}

void GameMapMaker::setEnemySpawner()
{
	std::cout << "SET ENEMY SPAWNER" << "\n\n";
	
	std::cout << "Random pos:";
	std::cin >> this->enemyRandomSpawnPos;

	while (std::cin.fail() || this->enemyRandomSpawnPos < 0 || this->enemyRandomSpawnPos > 1)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Random pos:";
		std::cin >> this->enemyRandomSpawnPos;
	}

	std::cout << "Max Velocity:";
	std::cin >> this->enemyMaxVelocity;

	while (std::cin.fail() || this->enemyMaxVelocity < -1)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Max Velocity:";
		std::cin >> this->enemyMaxVelocity;
	}

	std::cout << "Type:"; 
	std::cin >> this->enemyType;

	while (std::cin.fail() || this->enemyType > Enemy::nrOfTypes)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Type:";
		std::cin >> this->enemyType;
	}

	std::cout << "Level Interval:";
	std::cin >> this->enemyLevelInterval;

	while (std::cin.fail() || this->enemyLevelInterval <= 0)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Level Interval:";
		std::cin >> this->enemyLevelInterval;
	}

	std::cout << "Number of enemies:";
	std::cin >> this->nrOfEnemies;

	while (std::cin.fail() || this->nrOfEnemies < -1 || this->nrOfEnemies > 50)
	{
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Number of enemies:";
		std::cin >> this->nrOfEnemies;
	}

	std::cin.clear();
	std::cin.ignore(100, '\n');
}

void GameMapMaker::initView()
{
	this->mainView.setSize(Vector2f(this->window->getSize()));
	this->mainView.setCenter(Vector2f(
		this->window->getSize().x / 2,
		this->window->getSize().y / 2
	));
}

void GameMapMaker::initTextures()
{

}

void GameMapMaker::initText()
{
	//Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	//Selector text
	this->selectorText.setString("NONE");
	this->selectorText.setFont(this->font);
	this->selectorText.setCharacterSize(14);
	this->selectorText.setColor(Color::White);
	this->selectorText.setPosition(Vector2f(this->mousePosWindow));

	//Enemyspawner text
	this->enemySpawnerText.setString("NONE");
	this->enemySpawnerText.setFont(this->font);
	this->enemySpawnerText.setCharacterSize(14);
	this->enemySpawnerText.setColor(Color::White);
	this->enemySpawnerText.setPosition(Vector2f(this->mousePosWindow));
}

void GameMapMaker::initButtons()
{
	//WButton temp(this->font, "EnemySpawnerSelect", 12, Vector2f(600, 600), 0);

	////Add enemyspawnerselect button
	//this->buttons.add(temp);
}

void GameMapMaker::initUI()
{
	this->windowUI = true;

	this->textureX = 0;
	this->textureY = 0;
	this->selector.setSize(Vector2f(Galaxy::gridSize, Galaxy::gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineColor(Color::Green);
	this->selector.setOutlineThickness(2.f);

	this->textureSelector.setTexture(Tile::textures);
}

void GameMapMaker::initMap()
{
	this->stageName = "EMPTY";
	this->stage = new Stage(10, 10);
}

void GameMapMaker::initialize()
{
	//Init view
	this->initView();

	//INit textures
	this->initTextures();

	//Init map
	this->initMap();

	//Init text
	this->initText();

	//Init buttons
	this->initButtons();

	//Init UI
	this->initUI();
}

void GameMapMaker::updateMousePositions()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosWorld = this->window->mapPixelToCoords(this->mousePosWindow);
	
	if (windowUI)
	{
		this->mousePosGrid.x = this->mousePosWindow.x / (Galaxy::gridSize + 1);
		this->mousePosGrid.y = this->mousePosWindow.y / (Galaxy::gridSize + 1);
	}
	else
	{
		this->mousePosGrid.x = this->mousePosWorld.x / Galaxy::gridSize;
		this->mousePosGrid.y = this->mousePosWorld.y / Galaxy::gridSize;
		if (this->mousePosGrid.x < 0)
			this->mousePosGrid.x = 0;
		if (this->mousePosGrid.y < 0)
			this->mousePosGrid.y = 0;
		if (this->mousePosGrid.x >= this->stage->getSizeX())
			this->mousePosGrid.x = this->stage->getSizeX() - 1;
		if (this->mousePosGrid.y >= this->stage->getSizeY())
			this->mousePosGrid.y = this->stage->getSizeY() - 1;
	}

}

void GameMapMaker::updateView(const float &dt)
{
	float speed = 0.f;
	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		speed = 50.f;
	}
	else
	{
		speed = 20.f;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->mainView.move(0.f, -speed * dt * this->dtMultiplier);		
	}
	else if(Keyboard::isKeyPressed(Keyboard::S))
	{
		this->mainView.move(0.f, speed * dt * this->dtMultiplier);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->mainView.move(-speed * dt * this->dtMultiplier, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->mainView.move(speed * dt * this->dtMultiplier, 0.f);
	}
}

void GameMapMaker::updateTimers(const float &dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void GameMapMaker::mapUpdate(const float &dt)
{
	this->stage->update(dt, this->mainView, true);
}

void GameMapMaker::updateControls()
{
	//SWITCH WINDOW/VIEW UI
	if (Keyboard::isKeyPressed(Keyboard::Tab) && this->keyTime >= this->keyTimeMax)
	{
		if(this->windowUI)
			this->windowUI = false;
		else 
			this->windowUI = true;

		std::cout << this->windowUI << "\n";

		this->keyTime = 0.f;
	}

	//ADD/REMOVE TILES
	if (this->windowUI)
	{
		//Select a texture
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->textureX = this->mousePosGrid.x * (Galaxy::gridSize + 1);
			this->textureY = this->mousePosGrid.y * (Galaxy::gridSize + 1);
		}
	}
	else
	{
		this->updateAddRemoveTiles();
	}

	//New map
	if (Keyboard::isKeyPressed(Keyboard::N) 
		&& Keyboard::isKeyPressed(Keyboard::LControl)
		&& this->keyTime >= this->keyTimeMax)
	{
		this->newStage();

		this->keyTime = 0.f;
	}

	//Select regulat tile drawing
	if (Keyboard::isKeyPressed(Keyboard::T)
		&& Keyboard::isKeyPressed(Keyboard::LControl)
		&& this->keyTime >= this->keyTimeMax)
	{
		if (this->toolSelect == Stage::tileType::backgroundTile)
			this->toolSelect = Stage::tileType::regularTile;
		else
			this->toolSelect = Stage::tileType::backgroundTile;

		this->keyTime = 0.f;
	}

	//Toggle tile collider
	if (Keyboard::isKeyPressed(Keyboard::T)
		&& Keyboard::isKeyPressed(Keyboard::LShift)
		&& this->keyTime >= this->keyTimeMax)
	{
		if (this->tileCollider)
		{
			this->tileCollider = false;
			this->selector.setOutlineColor(Color::Green);
		}
		else
		{
			this->tileCollider = true;
			this->selector.setOutlineColor(Color::Red);
		}

		this->keyTime = 0.f;
	}

	//Select background tile drawing
	if (Keyboard::isKeyPressed(Keyboard::B)
		&& Keyboard::isKeyPressed(Keyboard::LControl)
		&& this->keyTime >= this->keyTimeMax)
	{
		if (this->toolSelect == Stage::tileType::backgroundTile)
			this->toolSelect = Stage::tileType::regularTile;
		else
			this->toolSelect = Stage::tileType::backgroundTile;

		this->keyTime = 0.f;
	}

	//Select background and background size
	if (Keyboard::isKeyPressed(Keyboard::G)
		&& Keyboard::isKeyPressed(Keyboard::LControl)
		&& this->keyTime >= this->keyTimeMax)
	{
		this->setBackground();

		this->keyTime = 0.f;
	}

	//SET enemyspawner
	if (Keyboard::isKeyPressed(Keyboard::E)
		&& Keyboard::isKeyPressed(Keyboard::LControl)
		&& Keyboard::isKeyPressed(Keyboard::LShift)
		&& this->keyTime >= this->keyTimeMax)
	{
		this->setEnemySpawner();

		this->keyTime = 0.f;
	}

	//Select enemyspawner
	if (Keyboard::isKeyPressed(Keyboard::E)
		&& Keyboard::isKeyPressed(Keyboard::LControl)
		&& this->keyTime >= this->keyTimeMax)
	{
		this->toolSelect = Stage::tileType::enemySpawner;

		this->keyTime = 0.f;
	}

	//Save stage
	if (Keyboard::isKeyPressed(Keyboard::LControl) 
		&& Keyboard::isKeyPressed(Keyboard::S)
		&& this->keyTime >= this->keyTimeMax)
	{
		this->saveStage();

		this->keyTime = 0.f;
	}

	//Load stage
	if (Keyboard::isKeyPressed(Keyboard::LControl)
		&& Keyboard::isKeyPressed(Keyboard::L)
		&& this->keyTime >= this->keyTimeMax)
	{
		this->loadStage();

		this->keyTime = 0.f;
	}
}

void GameMapMaker::updateAddRemoveTiles()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->toolSelect == Stage::tileType::regularTile
			|| this->toolSelect == Stage::tileType::backgroundTile)
		{
			this->stage->addTile(
				Tile(
					IntRect(
						this->textureX,
						this->textureY,
						Galaxy::gridSize,
						Galaxy::gridSize),
					Vector2f(
						this->mousePosGrid.x * Galaxy::gridSize,
						this->mousePosGrid.y * Galaxy::gridSize),
					this->tileCollider,
					false),
				this->mousePosGrid.x,
				this->mousePosGrid.y,
				this->toolSelect
			);
		}
		else if (this->toolSelect == Stage::tileType::enemySpawner)
		{
			this->enemyPosGrid = this->mousePosGrid;
			this->stage->addEnemySpawner(
				EnemySpawner(
					this->enemyPosGrid,
					this->enemyRandomSpawnPos,
					this->enemyMaxVelocity,
					this->enemyType,
					this->enemyLevelInterval,
					this->nrOfEnemies
				),
				this->mousePosGrid.x,
				this->mousePosGrid.y
			);
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right))
	{
		if (this->toolSelect == Stage::tileType::regularTile
			|| this->toolSelect == Stage::tileType::backgroundTile)
		{
			this->stage->removeTile(
				this->mousePosGrid.x,
				this->mousePosGrid.y,
				this->toolSelect
			);
		}
		else if (this->toolSelect == Stage::tileType::enemySpawner)
		{
			this->stage->removeEnemySpawner(
				this->mousePosGrid.x,
				this->mousePosGrid.y
			);
		}
	}
}

void GameMapMaker::updateText()
{
	if (this->windowUI)
	{
		this->selectorText.setPosition(Vector2f(this->mousePosWindow.x + 20.f, this->mousePosWindow.y));
		this->enemySpawnerText.setPosition(Vector2f(this->mousePosWindow.x + 20.f, this->mousePosWindow.y + 20.f));
	}
	else
	{
		this->selectorText.setPosition(Vector2f(this->mousePosWorld.x + 20.f, this->mousePosWorld.y));
		this->enemySpawnerText.setPosition(Vector2f(this->mousePosWorld.x + 20.f, this->mousePosWorld.y + 20.f));
	}

	if (this->toolSelect == Stage::tileType::backgroundTile)
		this->selectorText.setString(std::string("BACKGROUND TILE " + std::to_string(this->tileCollider)));
	else if(this->toolSelect == Stage::tileType::regularTile)
		this->selectorText.setString(std::string("REGULAR TILE " + std::to_string(this->tileCollider)));
	else if (this->toolSelect == Stage::tileType::enemySpawner)
		this->selectorText.setString("ENEMY SPAWNER");

	this->enemySpawnerText.setString(
		"Random pos: " + std::to_string(this->enemyRandomSpawnPos) +
		"\nType: " + std::to_string(this->enemyType) +
		"\nLevel Interval: " + std::to_string(this->enemyLevelInterval) +
		"\nNrOfEnemies: " + std::to_string(this->nrOfEnemies)
	);
}

void GameMapMaker::updateButtons()
{
	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i].update(this->mousePosWorld);
	}
}

void GameMapMaker::updateUI()
{
	if (this->windowUI)
	{
		this->selector.setPosition(
			this->mousePosGrid.x * (Galaxy::gridSize + 1),
			this->mousePosGrid.y * (Galaxy::gridSize + 1)
		);
	}
	else
	{
		this->selector.setPosition(
			this->mousePosGrid.x * (Galaxy::gridSize),
			this->mousePosGrid.y * (Galaxy::gridSize)
		);
	}
}

void GameMapMaker::update(const float &dt)
{
	//Timers UPDATE
	this->updateTimers(dt);

	//Mouse positions
	this->updateMousePositions();

	//Fullscreen
	this->toggleFullscreen();

	//General controls
	this->updateControls();

	//Map
	this->mapUpdate(dt);

	//Text update
	this->updateText();

	//Button update
	this->updateButtons();

	//UI update
	this->updateUI();

	//View
	this->updateView(dt);

}

void GameMapMaker::drawText()
{
	this->window->draw(this->selectorText);
	this->window->draw(this->enemySpawnerText);
}

void GameMapMaker::drawUIWindow()
{
	this->window->draw(this->textureSelector);

	this->window->draw(this->selector);	
}

void GameMapMaker::drawUIView()
{
	this->window->draw(this->selector);

	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i].draw(*this->window);
	}
}

void GameMapMaker::drawMap()
{
	this->stage->draw(
		*this->window,
		this->mainView,
		true,
		this->font
	);
}

void GameMapMaker::draw()
{
	//CLEAR AND BEGIN DRAW
	this->window->clear();

	//Set view
	this->window->setView(this->mainView);

	//Draw map
	this->drawMap();

	//Draw UI

	//Draw text
	this->drawText();

	//Set view
	if (this->windowUI)
	{
		this->window->setView(this->window->getDefaultView());

		this->drawUIWindow();
	}
	else
	{
		this->window->setView(this->mainView);

		this->drawUIView();
	}

	//FINISH DRAW
	this->window->display();
}
