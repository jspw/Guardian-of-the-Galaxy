#include "Bullet.h"

dArr<Texture> Bullet::textures;
int Bullet::nrOfTextures;

void Bullet::initTextures()
{
	Texture temp;
	
	temp.loadFromFile("Textures/Guns/rayTex01.png");
	Bullet::textures.add(temp);
	temp.loadFromFile("Textures/Guns/missileTex01.png");
	Bullet::textures.add(temp);
	temp.loadFromFile("Textures/Guns/missileHTex01.png");
	Bullet::textures.add(temp);
	temp.loadFromFile("Textures/Guns/roundBulletRed.png");
	Bullet::textures.add(temp);

	Bullet::nrOfTextures = Bullet::textures.size();
}

Bullet::Bullet(int type,
	Vector2f position, Vector2f scale,
	Vector2f direction, float initialVelocity,
	float maxVelocity, float acceleration,
	int damage)
{
	this->dtMultiplier = 62.5f;

	this->damage = damage;

	if (type >= Bullet::nrOfTextures)
	{
		std::cout << "ERROR NO SUCH BULLET TYPE!" << "\n\n";
		type = Bullet::nrOfTextures-1;
	}

	this->type = type;

	if (this->type >= 0)
		this->sprite.setTexture(Bullet::textures[this->type]);
	else
		std::cout << "ERROR COULD NOT SET TEXTURE, CONSTRUCTOR BULLET" << "\n\n";

	this->initialVelocity = initialVelocity;
	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;
	this->direction = direction;
	this->currentVelocity = Vector2f(
		initialVelocity * this->direction.x,
		initialVelocity * this->direction.y);

	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);

	this->sprite.setScale(scale);
	this->sprite.setPosition(position);
	this->sprite.setRotation(atan2(this->direction.y, this->direction.x) * 180 / 3.14159265359);
}

Bullet::~Bullet()
{

}

void Bullet::Movement(const float &dt)
{
	if (this->acceleration > 0.f)
	{
		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0.f
			|| this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0.f)
			this->currentVelocity.x += this->acceleration 
			* this->direction.x 
			* dt * this->dtMultiplier;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0.f
			|| this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0.f)
			this->currentVelocity.y += this->acceleration 
			* this->direction.y 
			* dt * this->dtMultiplier;
	}
	else
	{
		this->currentVelocity = Vector2f(
			this->maxVelocity * this->direction.x,
			this->maxVelocity * this->direction.y);
	}

	this->sprite.move(this->currentVelocity * dt * this->dtMultiplier);
}

void Bullet::Update(const float &dt)
{
	this->Movement(dt);
}

void Bullet::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}