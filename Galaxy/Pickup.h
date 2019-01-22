#pragma once

#include"Upgrade.h"

class Pickup
{
private:
	float dtMultiplier;
	int type;

	Sprite sprite;

	float aliveTimerMax;
	float aliveTimer;

public:
	Pickup(
		Vector2f position,
		int type,
		float duration
	);
	virtual ~Pickup();

	inline const int& getType()const { return this->type; }
	inline const bool canDelete()const { return this->aliveTimer >= this->aliveTimerMax; }
	inline Vector2f getPosition() { return this->sprite.getPosition(); }
	
	bool checkCollision(FloatRect rect);

	void Update(const float &dt);
	void Draw(RenderTarget &target);

	//Static varaibles
	static dArr<Texture> textures;
	static int nrOfTextures;

	static void initTextures();
};

