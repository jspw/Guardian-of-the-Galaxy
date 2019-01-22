#pragma once

#include"Particle.h"

class Tile
{
private:
	//Core
	bool isCollider;
	bool isDamaging;
	double damage;

	//Positioning

	//Visual
	Sprite sprite;

public:
	Tile(
		IntRect textureRect,
		Vector2f pos,
		bool isCollider,
		bool isDamaging
	);
	virtual ~Tile();

	inline const Vector2f getPos()const { return this->sprite.getPosition(); }
	inline const FloatRect getBounds()const { return this->sprite.getGlobalBounds(); }
	inline const IntRect getTexRect()const { return this->sprite.getTextureRect(); }
	inline const bool getIsDamaging()const { return this->isDamaging; }
	inline const bool getIsCollider()const { return this->isCollider; }
	inline void setPos(float x, float y) { this->sprite.setPosition(Vector2f(x,y)); }
	inline void move(float x, float y) { this->sprite.move(x, y); }
	inline void setTexRect(int x, int y, int width, int height) { this->sprite.setTextureRect(IntRect(x, y, width, height)); }
	inline void setIsCollider(bool isCollider) { this->isCollider = isCollider; }
	inline void setIsDamaging(bool idDamaging) { this->isDamaging = isDamaging; }
	inline void setColor(const Color color) { this->sprite.setColor(color); }
	std::string getAsString()const;

	void update(const float &dt);
	void draw(RenderTarget &target);

	//Static
	static Texture textures;
	static int nrOfTextures;

	static void initTextures();
};

