#include "Tile.h"

//Static define
Texture Tile::textures;
int Tile::nrOfTextures = 1;

void Tile::initTextures()
{
	Tile::textures.loadFromFile("Textures/Map/textureSheet.png");
}

Tile::Tile(
	IntRect textureRect,
	Vector2f pos,
	bool isCollider,
	bool isDamaging
)
{
	this->sprite.setTexture(Tile::textures);
	this->sprite.setTextureRect(textureRect);
	this->sprite.setPosition(pos);

	this->isCollider = isCollider;
	this->isDamaging = isDamaging;

	this->damage = 20.0; //percent of hp
}

Tile::~Tile()
{

}

std::string Tile::getAsString()const
{
	return
		//IntRect
		std::to_string(this->sprite.getTextureRect().left) + " " +
		std::to_string(this->sprite.getTextureRect().top) + " " +
		std::to_string(this->sprite.getTextureRect().width) + " " +
		std::to_string(this->sprite.getTextureRect().height) + " " +
		//Position Vector2f
		std::to_string((int)this->sprite.getPosition().x / Galaxy::gridSize) + " " +
		std::to_string((int)this->sprite.getPosition().y / Galaxy::gridSize) + " " +
		//Stats
		std::to_string(isCollider) + " " +
		std::to_string(isDamaging) + " ";
}

void Tile::update(const float &dt)
{

}

void Tile::draw(RenderTarget &target)
{
	target.draw(this->sprite);
}