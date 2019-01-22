#include "Boss.h"

enum textures { BODY = 0};

//TEXTURE RULE: 0 for body, 1 for regular gun, 2 for regular bullet

Boss::Boss(dArr<Texture> &bodyTextures,
	dArr<Texture> &gunTextures,
	dArr<Texture> &bulletTextures,
	Vector2f position,
	int type)
{
	this->bodyTextures = &bodyTextures;
	this->gunTextures = &gunTextures;
	this->bulletTextures = &bulletTextures;
	this->type = type;

	switch (this->type)
	{
	case 0: //FIRST EASY BOSS
	
		this->sprite.setTexture((*this->bodyTextures)[0]);

		this->guns.add(BossGun(&(*this->gunTextures)[0], Vector2f(0.f, 0.f), 20.f));
		this->guns.add(BossGun(&(*this->gunTextures)[0], Vector2f(0.f, 0.f), 20.f));
		this->guns.add(BossGun(&(*this->gunTextures)[0], Vector2f(0.f, 0.f), 20.f));
			
		this->sprite.setPosition(position);

		break;

	case 1:

		break;

	default:

		break;
	}
}

Boss::~Boss()
{

}

void Boss::Movement()
{

}

void Boss::Update(const float &dt)
{
	for (size_t i = 0; i < this->guns.size(); i++)
	{
		this->guns[i].Update(dt);
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Update(dt);
	}
}

void Boss::Draw(RenderTarget &target)
{
	target.draw(this->sprite);

	for (size_t i = 0; i < this->guns.size(); i++)
	{
		this->guns[i].Draw(target);
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}