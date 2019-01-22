#pragma once

#include"Bullet.h"

class Player
{
private:
	//CORE
	float dtMultiplier;
	float keyTimeMax;
	float keyTime;

	unsigned playerNr;

	//Positions
	Vector2f playerCenter;

	//Timers
	float shootTimer;
	float shootTimerMax;
	float damageTimer;
	float damageTimerMax;
	float shieldTimer;
	float shieldTimerMax;
	float shieldRechargeTimer;
	float shieldRechargeTimerMax;
	float powerupTimerMax;
	float powerupTimer;

	Sprite sprite;
	RectangleShape hitBox;

	//Accessories
	Sprite mainGunSprite;
	dArr<Bullet> bullets;

	Sprite deflectorShield;
	bool shielding;

	Sprite lWing;
	Sprite rWing;
	Sprite cPit;
	Sprite aura;

	int lWingSelect;
	int rWingSelect;
	int cPitSelect;
	int auraSelect;

	dArr<int> controls;
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;
	Vector2f normDir;

	int level;
	int exp;
	int expNext;
	int statPoints;

	int cooling; //endurance
	int plating; //vigor
	int power; //strength
	int wiring; //agility

	int hp;
	int hpMax;
	int hpAdded;

	int damage;
	int damageMax;

	int score;

	int currentWeapon;

	//UPGRADES
	dArr<int> upgradesAcquired;
	int mainGunLevel;
	bool piercingShot;
	bool shield;
	bool dualMissiles01;
	bool dualMissiles02;

	//Powerups
	bool powerupRF;
	bool powerupXP;

public:
	Player(
		int UP = Keyboard::W, 
		int DOWN = Keyboard::S,
		int LEFT = Keyboard::A, 
		int RIGHT = Keyboard::D,
		int SHOOT = Keyboard::Space,
		int SHIELD = Keyboard::RAlt,
		int STATS = Keyboard::Tab,
		int CHANGE_LWING = Keyboard::Num1,
		int CHANGE_CPIT = Keyboard::Num2,
		int CHANGE_RWING = Keyboard::Num3,
		int CHANGE_AURA = Keyboard::Num4
	);
	virtual ~Player();

	//Accessors
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize()const { return this->bullets.size(); }
	
	inline Vector2f getPosition()const { return this->sprite.getPosition(); }
	inline void resetVelocity() { this->currentVelocity = Vector2f(0.f, 0.f); }
	inline void move(float x, float y) { this->sprite.move(x, y); this->mainGunSprite.move(x, y); }
	inline const Vector2f& getNormDir()const { return this->normDir; }
	inline FloatRect getBounds()const { return this->sprite.getGlobalBounds(); }
	void setPos(float x, float y);
	
	inline const bool intersects(FloatRect rect)const { return this->sprite.getGlobalBounds().intersects(rect); }

	inline const String getHpAsString()const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
	inline const int& getHp()const { return this->hp; }
	inline const int& getHpMax()const { return this->hpMax; }
	inline bool isAlive()const { return this->hp > 0; }
	void gainHP(int hp);
	void upgradeHP();

	int getDamage()const;
	void takeDamage(int damage);
	inline bool isShielding()const { return this->shielding; }

	inline const int& getPlayerNr()const { return this->playerNr; }
	
	inline const int& getLevel()const { return this->level; }
	inline const int& getExp()const { return this->exp; }
	inline const int& getExpNext()const { return this->expNext; }
	bool gainExp(int exp);
	inline void addStatPoint() { this->statPoints++; }
	void addStatPointRandom();
	bool playerShowStatsIsPressed();
	std::string getStatsAsString()const;
	
	inline void gainScore(int score) { this->score += score; }
	inline const int getScore()const { return this->score; }
	
	inline bool isDamageCooldown()const { return this->damageTimer < this->damageTimerMax; }
	inline float getShieldTimer()const { return this->shieldTimer; }
	inline float getShieldTimerMax()const { return this->shieldTimerMax; }
	inline float getShieldRechargeTimer()const { return this->shieldRechargeTimer; }
	inline float getShieldRechargeTimerMax()const { return this->shieldRechargeTimerMax; }

	void setGunLevel(int gunLevel);
	inline const int& getGunLevel()const { return this->mainGunLevel; }
	inline void enablePiercingShot() { this->piercingShot = true; }
	inline bool getPiercingShot()const { return this->piercingShot; }
	inline void enableShield() { this->shield = true; }
	inline void enableDualMissiles01() { this->dualMissiles01 = true; }
	inline void enableDualMissiles02() { this->dualMissiles02 = true; }
	inline dArr<int>& getAcquiredUpgrades() { return this->upgradesAcquired; }

	inline float getPowerupTimer()const { return this->powerupTimer; }
	inline float getPowerupTimerMax()const { return this->powerupTimerMax; }
	inline bool getPowerupRF()const { return this->powerupRF; }
	inline bool getPowerupXP()const { return this->powerupXP; }
	inline void enablePowerupRF() { this->powerupRF = true; this->powerupTimer = this->powerupTimerMax; }
	inline void enablePowerupXP() { this->powerupXP = true; this->powerupTimer = this->powerupTimerMax; }

	//Functions
	void reset();
	bool updateLeveling();
	void updateStats();
	void changeAccessories(const float &dt);
	void updateAccessories(const float &dt, const float scrollSpeed);
	void updatePowerups();
	void combat(const float &dt);
	void movement(View &view, const float &dtconst, float scrollSpeed);
	void update(View &view, const float &dt, const float scrollSpeed);
	void draw(RenderTarget &target);

	//Regular functions
	float vectorLength(Vector2f v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	Vector2f normalize(Vector2f v, float length)
	{
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}

	//Statics
	static unsigned players;

	//Static Textures
	static dArr<Texture> bodyTextures;
	static dArr<Texture> mainGunTextures;
	static dArr<Texture> shieldTextures;
	static dArr<Texture> lWingTextures;
	static dArr<Texture> rWingTextures;
	static dArr<Texture> cPitTextures;
	static dArr<Texture> auraTextures;

	static void initTextures();

	enum weapons {LASER_NORMAL = 0, MISSILE_LIGHT, MISSILE_HEAVY };
	enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT, SHIELD, STATS, CHANGE_LWING, CHANGE_CPIT, CHANGE_RWING, CHANGE_AURA };
};

