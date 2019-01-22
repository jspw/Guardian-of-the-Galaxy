#include "Particle.h"

int Particle::nrOfTextures;
dArr<Texture> Particle::textures;

void Particle::initTextures()
{
	Texture temp;

	temp.loadFromFile("Textures/Particles/particle01.png");
	Particle::textures.add(temp);

	Particle::nrOfTextures = Particle::textures.size();
}

Particle::Particle(
	Vector2f pos,
	int textureIndex,
	Vector2f dir,
	float maxVel,
	float maxRotation,
	float lifeTime,
	Color color
)
{
	this->dtMultiplier = 62.5f;

	this->sprite.setTexture(Particle::textures[textureIndex]);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
		);
	this->sprite.setPosition(pos);
	this->sprite.setScale(Vector2f(1, 1));
	this->sprite.setColor(color);
	this->color = color;

	//From -10 to 10
	this->dir.x = (rand() % 20 + static_cast<int>(dir.x)) - 10;
	this->dir.y = (rand() % 20 + static_cast<int>(dir.y)) - 10;

	this->dir = normalize(this->dir, vectorLength(this->dir));

	this->deceleration = 0.2f;
	this->maxVel = maxVel;
	this->currentVel.x = maxVel * this->dir.x;
	this->currentVel.y = maxVel * this->dir.y;
	this->maxRotation = maxRotation;

	this->lifeTimeMax = lifeTime;
	this->lifeTime = lifeTime;
}

Particle::~Particle()
{

}

void Particle::update(const float &dt)
{
	//Lifetime
	double lifeTimePercent = 0.f;
	if (this->lifeTime > 0.f)
	{
		this->lifeTime -= 1.f * dt * this->dtMultiplier;

		lifeTimePercent = static_cast<double>(this->lifeTime / this->lifeTimeMax);

		//Reduce alpha
		if(this->sprite.getColor().a > 0)	
		{
			this->sprite.setColor(Color(
				this->color.r, 
				this->color.g,
				this->color.b,
				this->sprite.getColor().a)
			);

			if (this->sprite.getColor().a > 255)
				this->sprite.setColor(Color(
					this->color.r,
					this->color.g,
					this->color.b,
					0)
				);
		}

		//Movement
		this->currentVel.x += this->deceleration * -this->dir.x * dt * this->dtMultiplier;
		this->currentVel.y += this->deceleration * -this->dir.y * dt * this->dtMultiplier;

		this->sprite.move(
			this->currentVel.x * dt * this->dtMultiplier,
			this->currentVel.y * dt * this->dtMultiplier
			);

		this->sprite.rotate(this->maxRotation * dt * this->dtMultiplier);
	}
}

void Particle::draw(RenderTarget &target)
{
	target.draw(this->sprite);
}
