#pragma once

#include"TextTag.h"

class Bullet
{
private:
	float dtMultiplier;

	int type;
	Sprite sprite;

	Vector2f currentVelocity;
	float initialVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	int damage;

public:
	Bullet(int type,
		Vector2f position, Vector2f scale,
		Vector2f direction, float initialVelocity,
		float maxVelocity, float acceleration,
		int damage);
	virtual ~Bullet();

	//Accessors
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline const Vector2f& getPosition()const { return this->sprite.getPosition(); }
	inline void setPosition(Vector2f position) { this->sprite.setPosition(position); }
	inline Vector2f getNormDir() { return normalize(this->currentVelocity, vectorLength(this->currentVelocity)); }
	inline Vector2f getVel()const { return this->currentVelocity; }
	inline int getDamage()const { return this->damage; }

	//Functions
	void Movement(const float &dt);

	void Update(const float &dt);
	void Draw(RenderTarget &target);

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

	//Static
	enum bullets { 
		LASER_RED = 0, 
		MISSILE_LIGHT_RIGHT, 
		MISSILE_HEAVY_RIGHT, 
		BULLET_CIRCULAR_RED 
	};

	static dArr<Texture> textures;
	static int nrOfTextures;

	static void initTextures();
};

