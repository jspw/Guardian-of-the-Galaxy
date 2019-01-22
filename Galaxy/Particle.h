#pragma once

#include"Powerup.h"

class Particle
{
public:
	float dtMultiplier;
	Sprite sprite;
	Vector2f dir;
	Vector2f currentVel;
	float maxVel;
	float deceleration;
	float maxRotation;
	float lifeTimeMax;
	float lifeTime;
	Color color;

	Particle(
		Vector2f pos,
		int textureIndex,
		Vector2f dir,
		float maxVel,
		float maxRotation,
		float lifeTime,
		Color color
	);

	~Particle(); 

	inline bool readyToDel()const { return this->lifeTime <= 0.f; }

	void update(const float &dt);
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

	//Static
	static int nrOfTextures;
	static dArr<Texture> textures;

	static void initTextures();

	enum particles { 
		TRIANGULAR = 0 
	};

};

