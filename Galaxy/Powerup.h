#pragma once

#include"EnemySpawner.h"

enum powerupTypes {RF = 0, XP2};

class Powerup
{
private:
	float dtMultiplier;

	Sprite sprite;

	float timerMax;
	float timer;
	int type;

public:
	Powerup(int type, float timerMax, Vector2f pos);
	virtual ~Powerup();

	//Accessors
	inline int getType()const { return this->type; }
	inline bool isActive()const { return this->timer > 0; }
	inline Vector2f pos()const { return this->sprite.getPosition(); }
	inline FloatRect getBounds()const { return this->sprite.getGlobalBounds(); }
	inline bool collide(FloatRect rect)const { return this->sprite.getGlobalBounds().intersects(rect); }
	inline bool canRemove()const { return this->timer <= 0.f; }

	//Functions
	void update(const float &dt);
	void draw(RenderTarget &target);

	//Static
	static int nrOfTextures;
	static dArr<Texture> textures;

	static void initTextures();

	enum powerups { 
		RAPIDFIRE = 0, 
		EXPERIENCE_DOUBLE
	};
};

