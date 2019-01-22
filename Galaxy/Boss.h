#pragma once

#include"Bullet.h"

using namespace sf;

class Boss
{
private:
	
	class BossGun
	{
	private:
		float dtMultiplier;

		Sprite gunSprite;

		float shootTimerMax;
		float shootTimer;

	public:
		BossGun(Texture *texture, 
			Vector2f position, 
			float shootTimerMax)
		{
			this->shootTimerMax = shootTimerMax;
			this->shootTimer = this->shootTimerMax;
			

			this->gunSprite.setTexture(*texture);
			this->gunSprite.setPosition(position);
		}
		~BossGun()
		{

		}

		void Update(const float &dt)
		{

		}

		void Draw(RenderTarget &target)
		{
			target.draw(this->gunSprite);
		}
	};
	
	float dtMultiplier;

	int type;
	int nrOfGuns;

	dArr<Texture> *bodyTextures;
	dArr<Texture> *gunTextures;
	dArr<Texture> *bulletTextures;
	Sprite sprite;
	dArr<BossGun> guns;
	dArr<Bullet> bullets;

	int damageMin;
	int damageMax;

	int hpMax;
	int hp;

public:
	Boss(dArr<Texture> &bodyTextures,
		dArr<Texture> &gunTextures,
		dArr<Texture> &bulletTextures,
		Vector2f position,
		int type);
	virtual ~Boss();

	void Movement();
	void Update(const float &dt);
	void Draw(RenderTarget &target);
};

