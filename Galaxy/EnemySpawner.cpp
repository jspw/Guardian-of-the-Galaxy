#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(
	Vector2i gridPos,
	bool randomSpawnPos,
	int maxVelocity,
	int type,
	int levelInterval,
	int nrOfEnemies
)
{
	this->used = false;
	this->gridPosition = gridPos;
	this->randomSpawnPos = randomSpawnPos;
	this->maxVelocity = maxVelocity;
	this->type = type;
	this->levelInterval = levelInterval;
	this->nrOfEnemies = nrOfEnemies;
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::updateTimer()
{

}

bool EnemySpawner::isInScreen(View &view)
{
	return true;
}

void EnemySpawner::spawn()
{

}

std::string EnemySpawner::getAsString()const
{
	return std::to_string(this->gridPosition.x) + " " +
		std::to_string(this->gridPosition.y) + " " +
		std::to_string(this->randomSpawnPos) + " " +
		std::to_string(this->maxVelocity) + " " +
		std::to_string(this->type) + " " +
		std::to_string(this->levelInterval) + " " +
		std::to_string(this->nrOfEnemies) + " ";
}

void EnemySpawner::update(View &view)
{

}

void EnemySpawner::draw(RenderTarget &target, Font &font)
{
	RectangleShape shape;
	shape.setFillColor(Color::White);
	shape.setSize(Vector2f(Galaxy::gridSize, Galaxy::gridSize));
	shape.setPosition(this->gridPosition.x * Galaxy::gridSize, this->gridPosition.y * Galaxy::gridSize);
	if (this->type >= 0)
		shape.setTexture(&Enemy::textures[this->type]);

	Text text;
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(Color::Red);
	text.setPosition(shape.getPosition());
	text.setString(
		"Max Vel: " + std::to_string(this->maxVelocity) + "\n" +
		"Type: " + std::to_string(this->type) + "\n" +
		"LevelInterval: " + std::to_string(this->levelInterval) + "\n" +
		"NrOfE: " + std::to_string(this->nrOfEnemies) + "\n"
	);

	
	target.draw(shape);
	target.draw(text);
}