#pragma once

#include"Player.h"
#include"Enemy.h"
#include"Boss.h"
#include"Map.h"

class GameMapMaker
{
private:

	//GameMapMaker
	RenderWindow *window;
	View mainView;
	float dtMultiplier;
	float keyTimeMax;
	float keyTime;
	bool fullscreen;
	int toolSelect;
	int backgroundIndex;
	int backgroundWidth;
	int backgroundHeight;

	//Variables for tiles
	bool tileCollider;

	//Variables for enemySpawner
	Vector2i enemyPosGrid;
	bool enemyRandomSpawnPos;
	int enemyMaxVelocity;
	int enemyType;
	int enemyLevelInterval;
	int nrOfEnemies;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosWorld;
	Vector2i mousePosGrid;

	//UI
	bool windowUI;

	int textureX;
	int textureY;
	RectangleShape selector;

	Sprite textureSelector;

	//Buttons
	dArr<WButton> buttons;

	//Text
	Font font;
	Text selectorText;
	Text enemySpawnerText;

	//MAP
	std::string stageName;
	Stage *stage;

public:
	GameMapMaker(RenderWindow *window);
	virtual ~GameMapMaker();

	//Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	//Setters

	//Functions
	void toggleFullscreen();

	void newStage();
	void saveStage();
	void loadStage();
	void setBackground();
	void setEnemySpawner();

	void initView();
	void initButtons();
	void initTextures();
	void initText();
	void initUI();
	void initMap();
	void initialize();

	void updateMousePositions();
	void updateView(const float &dt);
	void updateTimers(const float &dt);
	void mapUpdate(const float &dt);
	void updateControls();
	void updateAddRemoveTiles();
	void updateText();
	void updateButtons();
	void updateUI();
	void update(const float &dt);

	void drawText();
	void drawUIWindow();
	void drawUIView();
	void drawMap();
	void draw();
};

