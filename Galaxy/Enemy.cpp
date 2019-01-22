#include "Enemy.h"

//Static define
dArr<Bullet> Enemy::enemyBullets;

dArr<Texture> Enemy::textures;
int Enemy::nrOfTextures;

void Enemy::initTextures()
{
	Texture temp;
	
	temp.loadFromFile("Textures/enemyMoveLeft.png");
	Enemy::textures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyFollow.png");
	Enemy::textures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyMoveLeft.png");
	Enemy::textures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyMoveLeftShoot.png");
	Enemy::textures.add(Texture(temp));

	Enemy::nrOfTextures = Enemy::textures.size();
}

int Enemy::nrOfTypes = 4;

Enemy::Enemy(
	View& view,
	bool randomPos,
	Vector2f position, 
	Vector2f moveDirection,
	float maxVelocity,
	int type,
	int scalar,
	int playerFollowNr)
{
	this->dtMultiplier = 62.5f;

	this->type = type;

	if (this->type >= Enemy::nrOfTextures || this->type < 0)
		std::cout << "NO TEXTURE FOR THIS TYPE! ERROR CONSTRUCTOR ENEMY!" << "\n";
	else
		this->sprite.setTexture(Enemy::textures[this->type]);

	this->sprite.setOrigin
	(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);
	
	this->color = Color::White;
	this->damageColor = Color::Red;

	this->damageTimerMax = 4.f;
	this->damageTimer = 0;

	this->nrOfBullets = 0;
	this->shootTimerMax = 50.f;
	this->shootTimer = this->shootTimerMax;

	this->moveDirection = moveDirection;

	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.setScale(Vector2f(0.11f, 0.11f));
		this->hpMax = (rand()% 5 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 3 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		if (maxVelocity < 0)
			this->maxVelocity = rand() % 20 + 5;
		else
			this->maxVelocity = maxVelocity;
			break;

	case FOLLOW:
		this->sprite.setScale(Vector2f(0.08f, 0.08f));
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		if (maxVelocity < 0)
			this->maxVelocity = rand() % 6 + 3;
		else
			this->maxVelocity = maxVelocity;
			break;

	case MOVELEFTSHOOT:
		this->color = Color(150, 150, 170, 255);
		this->sprite.setScale(Vector2f(0.09f, 0.09f));
		this->hpMax = (rand() % 5 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 3 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		
		if (maxVelocity < 0)
			this->maxVelocity = rand() % 10 + 5;
		else
			this->maxVelocity = maxVelocity;
		
		this->nrOfBullets = 3;
		this->shootTimerMax = 8.f;
		this->shootTimer = 0.f;
		break;

	case MOVELEFTSHOOTPLAYER:
		this->sprite.setScale(Vector2f(0.10f, 0.10f));
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		
		if (maxVelocity < 0)
			this->maxVelocity = rand() % 10 + 3;
		else
			this->maxVelocity = maxVelocity;
		
		this->shootTimerMax = 50.f;
		this->shootTimer = 0.f;
		break;

	default:
		this->hpMax = (rand() % 2 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		if (maxVelocity < 0)
			this->maxVelocity = rand() % 6 + 3;
		else
			this->maxVelocity = maxVelocity;
			break;
	}

	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->playerFollowNr = playerFollowNr;

	if (randomPos)
	{
		this->sprite.setPosition(
			(view.getCenter().x + view.getSize().x / 2),
			rand() % static_cast<int>((view.getCenter().y + view.getSize().y)) + static_cast<int>((view.getCenter().y - view.getSize().y)));
	}
	else
	{
		this->sprite.setPosition(position);
	}
}

Enemy::~Enemy()
{

}

void Enemy::collision()
{
	this->damageTimer = this->damageTimerMax;
}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	this->damageTimer = this->damageTimerMax;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Enemy::Update(const float &dt, Vector2f playerPosition)
{
	switch (this->type)
	{
	case MOVELEFT:

		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier
		);

		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		break;

	case FOLLOW:

		if (this->sprite.getPosition().x > playerPosition.x)
		{
			this->moveDirection.x = playerPosition.x - this->sprite.getPosition().x;
			this->moveDirection.y = playerPosition.y - this->sprite.getPosition().y;
		}

		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		if (this->normalizedMoveDir.y > 0.3)
			this->normalizedMoveDir.y = 0.3;
		else if(this->normalizedMoveDir.y < -0.3)
			this->normalizedMoveDir.y = -0.3;

		if (this->normalizedMoveDir.x > -0.7)
			this->normalizedMoveDir.x = -0.7;

		this->sprite.setRotation(atan2(this->normalizedMoveDir.y, this->normalizedMoveDir.x) * 180 / 3.14159265359 + 180);

		this->sprite.move(
			this->normalizedMoveDir.x * this->maxVelocity * dt * this->dtMultiplier,
			this->normalizedMoveDir.y * this->maxVelocity * dt * this->dtMultiplier
		);

			break;

	case MOVELEFTSHOOT:

		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier
		);

		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		//Shoot
		if (shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;

		if (this->shootTimer >= this->shootTimerMax && this->nrOfBullets > 0)
		{
			Enemy::enemyBullets.add(
				Bullet(
					Bullet::BULLET_CIRCULAR_RED,
					this->sprite.getPosition(),
					Vector2f(0.2f, 0.2f),
					this->normalizedMoveDir,
					this->maxVelocity,
					this->maxVelocity+5,
					0.2f,
					this->getDamage()
				)
			);

			this->shootTimer = 0.f;
			this->nrOfBullets--;
		}

			break;

	case MOVELEFTSHOOTPLAYER:

		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier
		);

		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		//Shoot
		if (shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;

		this->lookDirection.x = playerPosition.x - this->sprite.getPosition().x;
		this->lookDirection.y = playerPosition.y - this->sprite.getPosition().y;

		this->normalizedLookDir = normalize(this->lookDirection, vectorLength(this->lookDirection));

		this->sprite.setRotation(atan2(this->normalizedLookDir.y, this->normalizedLookDir.x) * 180 / 3.14159265359 + 180);

		if (this->shootTimer >= this->shootTimerMax)
		{
			Enemy::enemyBullets.add(
				Bullet(
					Bullet::BULLET_CIRCULAR_RED,
					this->sprite.getPosition(),
					Vector2f(0.2f, 0.2f),
					this->normalizedLookDir,
					1.f, 
					5,
					0.2f,
					this->getDamage()
				)
			);

			this->shootTimer = 0.f;
		}

		break;

	default:

		break;
	}

	//Damaged
	if (this->damageTimer > 0.f)
	{
		this->damageTimer -= 1.f * dt * dtMultiplier;

		this->sprite.setColor(damageColor);

		this->sprite.move(
			10.f * -this->normalizedMoveDir.x * this->damageTimer * dt * dtMultiplier,
			10.f * -this->normalizedMoveDir.y * this->damageTimer * dt * dtMultiplier
		);
	}
	else
		this->sprite.setColor(color);
}

void Enemy::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}