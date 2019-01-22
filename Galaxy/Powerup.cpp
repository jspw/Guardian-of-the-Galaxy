#include "Powerup.h"

int Powerup::nrOfTextures;
dArr<Texture> Powerup::textures;

void Powerup::initTextures()
{
	Texture temp;

	temp.loadFromFile("Textures/Powerups/powerupRF.png");
	Powerup::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Powerups/powerupXP.png");
	Powerup::textures.add(Texture(temp));

	Powerup::nrOfTextures = Powerup::textures.size();
}

Powerup::Powerup(int type, float timerMax, Vector2f pos)
{
	this->dtMultiplier = 62.5f;
	this->type = type;
	this->timerMax = timerMax;
	this->timer = timerMax;

	if (this->type >= Powerup::nrOfTextures || this->type < 0)
		std::cout << "ERROR NO SUCH POWERUP TEXTURE OR TYPE! CONSTRUTOR POWERUP" << "\n\n";
	else
		this->sprite.setTexture(Powerup::textures[this->type]);
	
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
		);
	this->sprite.setScale(1.f, 1.f);
	this->sprite.setPosition(pos);
}

Powerup::~Powerup()
{

}

void Powerup::update(const float &dt)
{
	//Update timer
	if (this->timer > 0)
		this->timer -= 1.f * dt * this->dtMultiplier;

	this->sprite.rotate(5.f * dt * this->dtMultiplier);
}

void Powerup::draw(RenderTarget &target)
{
	target.draw(this->sprite);
}