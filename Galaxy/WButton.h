#pragma once

#include"Enemy.h"

class WButton
{
private:
	int id;
	Sprite sprite;
	Text text;

	bool idle;
	bool hover;
	bool pressed;
	
	Color colorIdle;
	Color colorHover;
	Color colorPressed;
	
public:
	WButton(
		int id,
		Font &font,
		std::string text,
		const unsigned int charSize,
		Vector2f pos,
		int textureIndex
	);
	virtual ~WButton();

	inline std::string getName() { return this->text.getString(); }
	inline int getId() { return this->id; }

	bool isPressed();
	bool isHover();
	bool isIdle();

	void update(Vector2f mousePos);
	void draw(RenderTarget &target);

	//Static
	static dArr<Texture> textures;
	static int nrOfTextures;

	static void initTextures();

};

