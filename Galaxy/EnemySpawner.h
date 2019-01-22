#pragma once

#include"MainMenu.h"

class EnemySpawner
{
private:
	bool used;
	Vector2i gridPosition;
	bool randomSpawnPos;
	int maxVelocity; // -1 = random
	int type; // -1 = random
	int levelInterval;
	int nrOfEnemies; // -1 = random ( 1 - 10 )
	
public:
	EnemySpawner(
		Vector2i gridPos,
		bool randomSpawnPos,
		int maxVelocity,
		int type,
		int levelInterval,
		int nrOfEnemies
	);

	virtual ~EnemySpawner();

	//Accessors
	inline Vector2i getGridPos()const { return this->gridPosition; }
	inline Vector2f getPos()const { return Vector2f(gridPosition.x * Galaxy::gridSize, gridPosition.y * Galaxy::gridSize); }
	inline int getRandomSpawnPos()const { return this->randomSpawnPos; }
	inline int getMaxVelocity()const { return this->maxVelocity; }
	inline int getType()const { return this->type; }
	inline int getLevelInterval()const { return this->levelInterval; }
	inline int getNrOfEnemies()const { return this->nrOfEnemies; }
	inline bool isUsed()const { return this->used; }

	//Modifiers
	inline void setUsed() { this->used = true; }
	inline void setUnused() { this->used = false; }

	//Functions
	void updateTimer();
	bool isInScreen(View &view);
	void spawn();
	std::string getAsString()const;

	void update(View &view);
	void draw(RenderTarget &target, Font &font);
};

