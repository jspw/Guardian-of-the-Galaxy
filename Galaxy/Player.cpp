#include "Player.h"

unsigned Player::players = 0;

dArr<Texture> Player::bodyTextures;
dArr<Texture> Player::mainGunTextures;
dArr<Texture> Player::shieldTextures;
dArr<Texture> Player::lWingTextures;
dArr<Texture> Player::rWingTextures;
dArr<Texture> Player::cPitTextures;
dArr<Texture> Player::auraTextures;

////sound effetc 
//
//SoundBuffer bf;
//bf.loadFromFile("fire.wav");
//Sound fire;
//fire.setBuffer(bf);

void Player::initTextures()
{
	Texture temp;

	//Init textures regular
	temp.loadFromFile("Textures/ship.png");
	Player::bodyTextures.add(temp);

	//Player guns
	temp.loadFromFile("Textures/Guns/gun01.png");
	Player::mainGunTextures.add(Texture(temp));
	temp.loadFromFile("Textures/Guns/gun02.png");
	Player::mainGunTextures.add(Texture(temp));
	temp.loadFromFile("Textures/Guns/gun03.png");
	Player::mainGunTextures.add(Texture(temp));

	//Player shields
	temp.loadFromFile("Textures/Player/shield.png");
	Player::shieldTextures.add(Texture(temp));

	//Init accessory textures
	std::ifstream in;

	in.open("Textures/Accessories/leftwings.txt");
	std::string fileName = "";

	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			temp.loadFromFile(fileName);
			Player::lWingTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/rightwings.txt");
	fileName = "";

	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			temp.loadFromFile(fileName);
			Player::rWingTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/cockpits.txt");
	fileName = "";

	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			temp.loadFromFile(fileName);
			Player::cPitTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/auras.txt");
	fileName = "";

	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			temp.loadFromFile(fileName);
			Player::auraTextures.add(Texture(temp));
		}
	}

	in.close();
}

Player::Player(
	int UP,
	int DOWN,
	int LEFT,
	int RIGHT,
	int SHOOT,
	int SHIELD,
	int STATS,
	int CHANGE_LWING,
	int CHANGE_CPIT,
	int CHANGE_RWING,
	int CHANGE_AURA)

	:level(1), exp(0),
	hp(1000), hpMax(1000),hpAdded(1000),
	statPoints(20), cooling(0), 
	plating(0), wiring(0), power(0),
	damage(1), damageMax(2),
	score(0)
{
	//Dt
	this->dtMultiplier = 62.5f;

	//Add number of players for coop
	this->playerNr = Player::players;
	Player::players++;

	//Keytime
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	//Stats
	this->expNext = 20 + static_cast<int>(
		(50 / 3)
		*((pow(level, 3) - 6 
			* pow(level, 2)) + 17 
			* level - 12)
		);

	//Textures & Sprites
	this->sprite.setTexture(Player::bodyTextures[0]);
	this->sprite.setScale(0.08f, 0.08f);
	this->sprite.setColor(Color(10, 10, 10, 255));
	this->sprite.setPosition(Vector2f(400.f, 300.f + Player::playerNr * 150.f));

	//Update positions
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	//Init main gun
	this->mainGunSprite.setTexture(Player::mainGunTextures[0]);
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2
	);

	this->mainGunSprite.rotate(90);

	this->mainGunSprite.setPosition(
		this->playerCenter.x + 20.f,
		this->playerCenter.y
	);
	this->mainGunSprite.setScale(0.9f, 0.9f);

	//Init shield
	this->deflectorShield.setTexture(Player::shieldTextures[0]);
	this->deflectorShield.setOrigin(
		this->deflectorShield.getGlobalBounds().width/2,
		this->deflectorShield.getGlobalBounds().height/2
		);
	this->deflectorShield.setPosition(this->playerCenter);
	this->deflectorShield.setScale(0.8f, 0.8f);

	//Accessories

	//Selectors
	this->lWingSelect = 1;
	this->rWingSelect = 1;
	this->cPitSelect = 1;
	this->auraSelect = 1;

	//Acceccory textures
	this->lWing.setTexture(Player::lWingTextures[this->rWingSelect]);
	this->rWing.setTexture(Player::rWingTextures[this->rWingSelect]);
	this->cPit.setTexture(Player::cPitTextures[this->cPitSelect]);
	this->aura.setTexture(Player::auraTextures[this->auraSelect]);

	//Init accessories
	float accScale = 0.7f;
	this->lWing.setOrigin(
		this->lWing.getGlobalBounds().width / 2,
		this->lWing.getGlobalBounds().height / 2
		);

	this->lWing.setPosition(this->playerCenter);
	this->lWing.setRotation(90.f);
	this->lWing.setScale(accScale, accScale);

	this->rWing.setOrigin(
		this->rWing.getGlobalBounds().width / 2,
		this->rWing.getGlobalBounds().height / 2
	);

	this->rWing.setPosition(this->playerCenter);
	this->rWing.setRotation(90.f);
	this->rWing.setScale(accScale, accScale);

	this->cPit.setOrigin(
		this->cPit.getGlobalBounds().width / 2,
		this->cPit.getGlobalBounds().height / 2
		);

	this->cPit.setPosition(this->playerCenter);
	this->cPit.setRotation(90.f);
	this->cPit.setScale(accScale, accScale);

	this->aura.setOrigin(
		this->aura.getGlobalBounds().width / 2,
		this->aura.getGlobalBounds().height / 2
		);

	this->aura.setPosition(this->playerCenter);
	this->aura.setRotation(90.f);
	this->aura.setScale(accScale, accScale);

	//Timers
	this->shootTimerMax = 40.f;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 40.f;
	this->damageTimer = this->damageTimerMax;
	this->shieldTimerMax = 50.f + this->cooling + (this->wiring / 2);;
	this->shieldTimer = this->shieldTimerMax;
	this->shieldRechargeTimerMax = 100.f;
	this->shieldRechargeTimer = this->shieldRechargeTimerMax;
	this->powerupTimerMax = 400.f;
	this->powerupTimer = 0.f;

	//Controls
	//FOLLOW CONTROLS ENUM TEMPLATE!
	this->controls.add(int(UP));
	this->controls.add(int(DOWN));
	this->controls.add(int(LEFT));
	this->controls.add(int(RIGHT));
	this->controls.add(int(SHOOT));
	this->controls.add(int(SHIELD));
	this->controls.add(int(STATS));
	this->controls.add(int(CHANGE_LWING));
	this->controls.add(int(CHANGE_CPIT));
	this->controls.add(int(CHANGE_RWING));
	this->controls.add(int(CHANGE_AURA));

	//Velocity & Acceleration
	this->maxVelocity = 25.f;
	this->acceleration = 0.8f;
	this->stabilizerForce = 0.3f;

	//Guns
	this->currentWeapon = Player::LASER_NORMAL;

	//Shields
	this->shielding = false;

	//Upgrades
	this->mainGunLevel = 0;
	this->piercingShot = false;
	this->shield = true;
	this->dualMissiles01 = false;
	this->dualMissiles02 = false;

	this->setGunLevel(0);

	//Powerups
	this->powerupRF = false;
	this->powerupXP = false;
}

Player::~Player()
{

}

void Player::setPos(float x, float y)
{
	this->sprite.setPosition(Vector2f(x, y)); this->mainGunSprite.setPosition(Vector2f(x, y));
	//Update positions
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;
}

int Player::getDamage()const
{ 
	int damage = 0;

	switch (this->currentWeapon)
	{
	case Player::LASER_NORMAL:

		damage = rand() % this->damageMax + this->damage;

		break;
	case Player::MISSILE_LIGHT:

		damage = rand() % this->damageMax + this->damage;
		damage *= 2;

		break;
	case Player::MISSILE_HEAVY:

		damage = rand() % this->damageMax + this->damage;
		damage *= 4;

		break;
	default:

		damage = rand() % this->damageMax + this->damage;

		break;
	}

	return damage;
}

void Player::takeDamage(int damage)
{ 
	this->hp -= damage; 

	this->damageTimer = 0;

	this->currentVelocity.x += -this->normDir.x*10.f;
	this->currentVelocity.y += -this->normDir.y*10.f;
}

bool Player::updateLeveling()
{
	if (this->exp >= this->expNext)
	{
		this->level++;
		this->statPoints++;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3)*((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));

		this->wiring++;
		this->cooling++;
		this->plating++;
		this->power++;

		this->updateStats();

		this->hp = hpMax;

		return true;
	}

	return false;
}

void Player::updateStats()
{
	this->hpMax = this->hpAdded + this->plating * 5;
	this->damageMax = 2 + this->power * 2;
	this->damage = 1 + this->power;
	this->shieldTimerMax = 50.f + this->cooling + (this->wiring / 2);
}

void Player::changeAccessories(const float &dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_LWING])) && this->keyTime >= this->keyTimeMax)
	{
		if (lWingSelect < Player::lWingTextures.size() - 1)
			lWingSelect++;
		else
			lWingSelect = 0;

		this->lWing.setTexture(Player::lWingTextures[lWingSelect]);

		this->keyTime = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_RWING])) && this->keyTime >= this->keyTimeMax)
	{
		if (rWingSelect < Player::rWingTextures.size() - 1)
			rWingSelect++;
		else
			rWingSelect = 0;

		this->rWing.setTexture(Player::rWingTextures[rWingSelect]);

		this->keyTime = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_CPIT])) && this->keyTime >= this->keyTimeMax)
	{
		if (cPitSelect < Player::cPitTextures.size() - 1)
			cPitSelect++;
		else
			cPitSelect = 0;

		this->cPit.setTexture(Player::cPitTextures[cPitSelect]);

		this->keyTime = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_AURA])) && this->keyTime >= this->keyTimeMax)
	{
		if (auraSelect < Player::auraTextures.size() - 1)
			auraSelect++;
		else
			auraSelect = 0;

		this->aura.setTexture(Player::auraTextures[auraSelect]);

		this->keyTime = 0;
	}
}

void Player::updateAccessories(const float &dt, const float scrollSpeed)
{
	//Set the position of gun to follow player
	this->mainGunSprite.setPosition(
		this->mainGunSprite.getPosition().x,
		this->playerCenter.y
	);

	//Set the position of the shield to follow player
	this->deflectorShield.setPosition(this->playerCenter);

	//Animate the main gun and correct it after firing
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x + 20.f)
	{
		this->mainGunSprite.move(
			scrollSpeed * dt * this->dtMultiplier + 
			5.f * dt * this->dtMultiplier 
			+ this->currentVelocity.x * dt * this->dtMultiplier, 0.f);
	}
	if (this->mainGunSprite.getPosition().x > this->playerCenter.x + 20.f)
	{
		this->mainGunSprite.setPosition(
			this->playerCenter.x + 20.f,
			this->playerCenter.y
		);
	}

	//Left wing
	this->lWing.setPosition(
		playerCenter.x + -abs(this->currentVelocity.x), 
		playerCenter.y + -abs(this->currentVelocity.x/2 + this->currentVelocity.y/2)
	);

	//Right wing
	this->rWing.setPosition(
		playerCenter.x + -abs(this->currentVelocity.x), 
		playerCenter.y + abs(this->currentVelocity.x / 2 + this->currentVelocity.y / 2)
	);

	//Cockpit
	this->cPit.setPosition(
		playerCenter.x + this->currentVelocity.x, 
		playerCenter.y
	);

	//Aura
	this->aura.setPosition(playerCenter);
	this->aura.rotate(3.f * dt * this->dtMultiplier);
}

void Player::updatePowerups()
{
	if (this->powerupTimer <= 0.f)
	{
		this->powerupRF = false;
		this->powerupXP = false;
	}
}

void Player::movement(View &view, const float &dt, const float scrollSpeed)
{
	//Update normalized direction
	this->normDir = normalize(this->currentVelocity, vectorLength(this->currentVelocity));

	//UP
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;
	
		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration
			* dt * this->dtMultiplier;
	}
	
	//DOWN
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
	{ 
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration
			* dt * this->dtMultiplier;
	}
	
	//LEFT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
	{ 
		this->direction.x = -1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration
			* dt * this->dtMultiplier;

	}
	
	//RIGHT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
	{ 
		this->direction.x = 1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration
			* dt * this->dtMultiplier;

	}

	//Drag force
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce
			* dt * this->dtMultiplier;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce
			* dt * this->dtMultiplier;

		if (this->currentVelocity.x > 0)
			this->currentVelocity.x = 0;
	}
	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce
			* dt * this->dtMultiplier;

		if (this->currentVelocity.y < 0)
			this->currentVelocity.y = 0;
	}
	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce
			* dt * this->dtMultiplier;

		if (this->currentVelocity.y > 0)
			this->currentVelocity.y = 0;
	}

	//Final move
	this->sprite.move(
		scrollSpeed * dt * this->dtMultiplier +
		this->currentVelocity.x * dt * this->dtMultiplier, 
		this->currentVelocity.y * dt * this->dtMultiplier);

	//Update positions
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	//Window collision
	//Left
	if (this->getPosition().x <= view.getCenter().x - view.getSize().x/2)
	{
		this->sprite.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.f, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}
	//Right
	else if (this->getPosition().x + this->getBounds().width >= view.getCenter().x + view.getSize().x / 2)
	{
		this->sprite.setPosition(view.getCenter().x + view.getSize().x / 2 - this->getBounds().width, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}	
	//Top
	if (this->getPosition().y <= view.getCenter().y - view.getSize().y / 2)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, view.getCenter().y - view.getSize().y / 2);
		this->currentVelocity.y = 0.f;
	}
	//Bottom
	else if (this->getPosition().y + this->getBounds().height >= view.getCenter().y + view.getSize().y / 2)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, view.getCenter().y + view.getSize().y / 2 - this->getBounds().height);
		this->currentVelocity.y = 0.f;
	}	
}

void Player::combat(const float &dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT]))
		&& this->shootTimer >= this->shootTimerMax)
	{
	
//		fireSound.play();
		if (this->currentWeapon == Player::LASER_NORMAL)
		{
			//Create bullet
			if (this->mainGunLevel == 0)
			{
				this->bullets.add(
					Bullet(
						Bullet::LASER_RED,
						Vector2f(this->playerCenter.x + 100.f, this->playerCenter.y),
						Vector2f(0.15f, 0.15f),
						Vector2f(1.f, 0.f),
						20.f, 
						60.f, 
						5.f, 
						this->getDamage()
					));
			}
			else if (this->mainGunLevel == 1)
			{
				this->bullets.add(
					Bullet(
						Bullet::LASER_RED,
						Vector2f(this->playerCenter.x + 100.f, this->playerCenter.y - 15.f),
						Vector2f(0.2f, 0.2f),
						Vector2f(1.f, 0.f),
						20.f, 
						60.f, 
						5.f,
						this->getDamage()
					)
				);

				this->bullets.add(
					Bullet(
						Bullet::LASER_RED,
						Vector2f(this->playerCenter.x + 100.f, this->playerCenter.y + 15.f),
						Vector2f(0.2f, 0.2f),
						Vector2f(1.f, 0.f),
						20.f, 
						60.f, 
						5.f,
						this->getDamage()
					)
				);
			}
			else if (this->mainGunLevel == 2)
			{
				this->bullets.add(
					Bullet(
						Bullet::LASER_RED,
						Vector2f(this->playerCenter.x + 100.f, this->playerCenter.y - 41.f),
						Vector2f(0.2f, 0.2f),
						Vector2f(1.f, 0.f),
						20.f, 
						60.f,
						5.f,
						this->getDamage()
					)
				);

				this->bullets.add(
					Bullet(
						Bullet::LASER_RED,
						Vector2f(this->playerCenter.x + 100.f, this->playerCenter.y),
						Vector2f(0.2f, 0.2f),
						Vector2f(1.f, 0.f),
						20.f, 
						60.f, 
						5.f,
						this->getDamage()
					)
				);

				this->bullets.add(
					Bullet(
						Bullet::LASER_RED,
						Vector2f(this->playerCenter.x + 100.f, this->playerCenter.y + 43.f),
						Vector2f(0.2f, 0.2f),
						Vector2f(1.f, 0.f),
						20.f, 
						60.f, 
						5.f,
						this->getDamage()
					)
				);
			}

			//Animate gun
			this->mainGunSprite.move(-40.f, 0.f);
		}
		else if (this->currentWeapon == Player::MISSILE_LIGHT)
		{
			//Create bullet
			this->bullets.add(
				Bullet(
					Bullet::MISSILE_LIGHT_RIGHT,
					Vector2f(this->playerCenter.x, this->playerCenter.y - 25.f),
					Vector2f(0.05f, 0.05f),
					Vector2f(1.f, 0.f), 
					0.f,
					50.f,
					1.f,
					this->getDamage()
				)
			);

			if (this->dualMissiles01)
			{
				this->bullets.add(
					Bullet(
						Bullet::MISSILE_LIGHT_RIGHT,
						Vector2f(this->playerCenter.x, this->playerCenter.y + 25.f),
						Vector2f(0.05f, 0.05f),
						Vector2f(1.f, 0.f),
						0.f, 
						50.f,
						1.f,
						this->getDamage()
					)
				);
			}
		}
		else if (this->currentWeapon == Player::MISSILE_HEAVY)
		{
			if (this->dualMissiles02)
			{
				
			}
		}
	
		this->shootTimer = 0; //RESET TIMER!
	}

	//SHIELDING
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHIELD])) && this->shield)
	{
		if (this->shieldTimer > 0 && this->shieldRechargeTimer >= this->shieldRechargeTimerMax)
		{
			this->shielding = true;
			this->shieldTimer -= 2.f * dt * this->dtMultiplier;

			//DEPLETE SHIELD
			if (this->shieldTimer <= 0.f)
				this->shieldRechargeTimer = 0.f;
		}
		else
			this->shielding = false;
	}
	else
	{
		this->shielding = false;
	}

	//DAMAGED
	if (this->isDamageCooldown())
	{
		if ((int)this->damageTimer % 2 == 0)
		{
			this->lWing.setColor(Color::Red);
			this->rWing.setColor(Color::Red);
			this->cPit.setColor(Color::Red);
		}
		else
		{
			this->lWing.setColor(Color::White);
			this->rWing.setColor(Color::White);
			this->cPit.setColor(Color::White);
		}
	}
	else
	{
		this->lWing.setColor(Color::White);
		this->rWing.setColor(Color::White);
		this->cPit.setColor(Color::White);
	}
}

Bullet& Player::getBullet(unsigned index)
{
	if (index < 0 || index > this->bullets.size())
		throw"OUT OF BOUNDS! PLAYER::GETBULLET!";

	return this->bullets[index];
}

void Player::removeBullet(unsigned index)
{
	if (index < 0 || index > this->bullets.size())
		throw"OUT OF BOUNDS! PLAYER::REMOVEBULLET!";

	this->bullets.remove(index);
}

void Player::setGunLevel(int gunLevel) 
{ 
	this->mainGunLevel = gunLevel; 

	if (this->mainGunLevel < Player::mainGunTextures.size())
		this->mainGunSprite.setTexture(Player::mainGunTextures[this->mainGunLevel]);
	else
		std::cout << "NO TEXTURE FOR THAT MAIN GUN!" << "\n";
}

void Player::addStatPointRandom()
{
	int r = rand() % 4;
	switch (r)
	{
	case 0:
		this->power++;
		break;
	case 1:
		this->wiring++;
		break;
	case 2:
		this->cooling++;
		break;
	case 3:
		this->plating++;
		break;
	default:
		break;
	}

	this->updateStats();
}

bool Player::gainExp(int exp)
{
	this->exp += exp;
	return this->updateLeveling();
}

void Player::gainHP(int hp)
{
	this->hp += hp;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player:: upgradeHP() 
{ 
	this->hpAdded += 10; 
	this->updateStats(); 
	this->hp = this->hpMax; 
}

bool Player::playerShowStatsIsPressed()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::STATS])))
		return true;

	return false;
}

std::string Player::getStatsAsString()const
{
	return
		"Level: " + std::to_string(this->level) +
		"\nExp: " + std::to_string(this->exp) + " / " + std::to_string(this->expNext) +
		"\nStatpoints: " + std::to_string(this->statPoints) +
		"\nHP: " + std::to_string(this->hp) + " / " + std::to_string(this->hpMax) + " ( +" + std::to_string(this->hpAdded) + ") "
		"\nDamage: " + std::to_string(this->damage) + " - " + std::to_string(this->damageMax) +
		"\n\nScore: " + std::to_string(this->score) +
		"\n\nPower: " + std::to_string(this->power) +
		"\nPlating: " + std::to_string(this->plating) +
		"\nWiring: " + std::to_string(this->wiring) +
		"\nCooling: " + std::to_string(this->cooling) +
		"\n\nShield Capacity: " + std::to_string(this->shieldTimerMax);
}

void Player::reset()
{
	//Reset sprites
	this->sprite.setPosition(Vector2f(400.f, 300.f + Player::playerNr * 150.f));

	//Reset stats
	this->hpMax = 1000;
	this->hpAdded = 100;
	this->hp = this->hpMax;
	this->wiring = 2;
	this->cooling = 2;
	this->power = 0;
	this->plating = 0;
	this->level = 5;
	this->exp = 10;
	this->expNext = 0;
	this->statPoints = 0;
	this->score = 230;
	this->updateStats();

	//Reset physics and movement
	this->currentVelocity.x = 0;
	this->currentVelocity.y = 0;

	//Reset arrays
	this->bullets.clear();
	this->upgradesAcquired.clear();

	//Reset weapon
	this->setGunLevel(Player::LASER_NORMAL);
	this->currentWeapon = LASER_NORMAL;

	//Reset upgrades
	this->dualMissiles01 = false;
	this->dualMissiles02 = false;
	this->shield = false;
	this->piercingShot = false;

	//Reseet powerups
	this->powerupRF = false;
	this->powerupXP = false;

	//Reset timers
	this->shootTimer = this->shootTimerMax;
	this->damageTimer = this->damageTimerMax;
	this->powerupTimer = 0;
	this->shieldTimer = this->shieldTimerMax;
	this->shieldRechargeTimer = this->shieldRechargeTimerMax;
}

void Player::update(View &view, const float &dt, const float scrollSpeed)
{
	//Update timers
	if (this->powerupRF)
	{
		this->shootTimerMax = 10.f;
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;
	}
	else
	{
		this->shootTimerMax = 20.f;
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;
	}

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer += 1.f * dt * this->dtMultiplier;

	if(this->shieldRechargeTimer < this->shieldRechargeTimerMax)
		this->shieldRechargeTimer += 1.f * dt * this->dtMultiplier;

	if (this->shieldTimer < this->shieldTimerMax 
		&& this->shieldRechargeTimer >= this->shieldRechargeTimerMax)
			this->shieldTimer += 1.f * dt * this->dtMultiplier;

	if (this->powerupTimer > 0.f)
		this->powerupTimer -= 1.f * dt * this->dtMultiplier;

	this->movement(view, dt, scrollSpeed);
	this->changeAccessories(dt);
	this->updateAccessories(dt, scrollSpeed);
	this->updatePowerups();
	this->combat(dt);
}

void Player::draw(RenderTarget &target)
{
	target.draw(this->aura);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}

	target.draw(this->mainGunSprite);

	target.draw(this->sprite);

	target.draw(this->cPit);
	target.draw(this->lWing);
	target.draw(this->rWing);

	if (this->shielding)
		target.draw(this->deflectorShield);
}