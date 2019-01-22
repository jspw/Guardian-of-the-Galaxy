#pragma once

#include"SFML\Graphics.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include <fstream>
#include"dArr.h"

using namespace sf;

class Upgrade
{
private:
	float dtMultiplier;

	int type;
	
	float aliveTimerMax;
	float aliveTimer;

	Sprite sprite;

public:
	Upgrade(
		Vector2f position,
		int type,
		float aliveTimerMax);

	virtual ~Upgrade();
	
	inline const int& getType()const { return this->type; }
	inline bool canDelete() { return this->aliveTimer >= this->aliveTimerMax; }
	
	bool checkCollision(FloatRect rect);

	void Update(const float &dt);
	void Draw(RenderTarget &target);

	//Static
	static int nrOfTextures;
	static dArr<Texture> textures;

	static void initTextures();

	enum upgrades { 
		STAT_POINT = 0,
		HEALTH_TANK,
		DOUBLE_RAY,
		TRIPLE_RAY,
		PIERCING_SHOT,
		SHIELD,
	};
};

