#pragma once

#include"Player.h"
#include"Boss.h"
#include"Map.h"

enum Mode {Survival = 0, Regular};

class Game
{
private:
	//Game Menu
	MainMenu mainMenu;

	//Game
	RenderWindow *window;
	View mainView;
	RenderTexture mainRenderTexture;
	Sprite mainRenderSprite;
	float dtMultiplier;
	bool paused;
	float keyTimeMax;
	float keyTime;
	bool fullscreen;
	int mode;
	bool Mplayer;
	
	//Score
	unsigned score;
	unsigned scoreMultiplier;
	Clock scoreTimer;
	int scoreTime;
	float multiplierTimerMax;
	float multiplierTimer;
	int multiplierAdder;
	int multiplierAdderMax;
	double bestScoreSecond;
	float difficultyTimer;
	int difficulty;

	//UI
	//Text
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text playerStatsText;
	Text enemyText;
	Text gameOverText;
	Text scoreText;
	Text controlsText;

	//Bars
	RectangleShape playerExpBar;
	RectangleShape playerShieldBar;
	RectangleShape playerPowerupBar;

	//Backgrounds
	RectangleShape playerStatsTextBack;

	//Texttags
	dArr<TextTag> textTags;

	//MAP
	int fromCol, toCol;
	int fromRow, toRow;
	Stage *stage;

	//Players
	dArr<Player> players;
	int playersAlive;

	//Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	
	//Bosses
	bool bossEncounter;
	dArr<Boss> bosses;

	//Pickups
	dArr<Pickup> pickups;

	//Upgrades
	dArr<Upgrade> upgrades;

	//Powerups
	dArr<Powerup> powerups;

	//Particles
	dArr<Particle> particles;

	//Pickup/Upgrade textures
	unsigned nrOfPickups;
	dArr<Texture> pickupTextures;

	//Enemy textures
	dArr<Texture> enemyTextures;
	dArr<Texture> enemyBulletTextures;

	//Boss Textures

public:
	Game(RenderWindow *window);
	virtual ~Game();

	//Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	//Setters

	//Functions
	void toggleFullscreen();
	void pauseGame();

	void initRT();
	void initView();
	void initTextures();
	void initMenues();
	void initUI();
	void initMap();
	void initialize();

	void updateView(const float &dt);
	void restartUpdate();
	void setEndingScoreboard();
	void updateTimers(const float &dt);
	void updateTimersUnpaused(const float &dt);
	void updateScore();
	void updateDifficulty();
	void updateUIPlayer(int index);
	void updateUIEnemy(int index);
	void updateWhilePaused(const float &dt);
	void playerUpdate(const float &dt);
	void playerBulletUpdate(const float &dt, const int i);
//	void playerCollisionUpdate(const float &dt, const int i);
	void enemyUpdate(const float &dt);
	void enemySpawnUpdate(const float &dt);
	void enemyBulletUpdate(const float &dt);
	void textTagsUpdate(const float &dt);
	void pickupsUpdate(const float &dt);
	void upgradesUpdate(const float &dt);
	void powerupsUpdate(const float &dt);
	void mapUpdate(const float &dt);
	void particlesUpdate(const float &dt);
	void update(const float &dt);

	void drawUI();
	void drawPlayers();
	void drawEnemies();
	void drawMap();
	void drawTextTags();
	void drawPickups();
	void drawUpgrades();
	void drawPowerups();
	void drawParticles();
	void draw();
};

