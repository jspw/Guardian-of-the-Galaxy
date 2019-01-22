#include "Upgrade.h"

dArr<Texture> Upgrade::textures;
int Upgrade::nrOfTextures;

void Upgrade::initTextures()
{
	Texture temp;

	temp.loadFromFile("Textures/Upgrades/statpoint.png");
	Upgrade::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Upgrades/healthtank.png");
	Upgrade::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Upgrades/doubleray.png");
	Upgrade::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Upgrades/tripleray.png");
	Upgrade::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Upgrades/piercingshot.png");
	Upgrade::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Upgrades/shield.png");
	Upgrade::textures.add(Texture(temp));
	Upgrade::nrOfTextures = Upgrade::textures.size();

	Upgrade::nrOfTextures = Upgrade::textures.size();
}


Upgrade::Upgrade(
	Vector2f position,
	int type,
	float aliveTimerMax
)
{
	this->dtMultiplier = 62.5f;

	this->aliveTimerMax = aliveTimerMax;
	this->aliveTimer = 0;

	this->type = type;

	if (this->type < Upgrade::nrOfTextures || this->type >= 0)
		this->sprite.setTexture(Upgrade::textures[this->type]);
	else
		std::cout << "ERROR NO TEXTURE FOR THAT UPGRADE TYPE, CONSTRUCTOR UPGRADE!" << "\n";

	this->sprite.setOrigin
	(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);

	this->sprite.setPosition(position);
}

Upgrade::~Upgrade()
{

}

bool Upgrade::checkCollision(FloatRect rect)
{
	if (this->sprite.getGlobalBounds().intersects(rect))
		return true;

	return false;
}

void Upgrade::Update(const float &dt)
{
	if (this->aliveTimer < this->aliveTimerMax)
		this->aliveTimer += 1.f * dt * this->dtMultiplier;

	this->sprite.rotate(5.f * dt * this->dtMultiplier);
}

void Upgrade::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}