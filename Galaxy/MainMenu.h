#pragma once

#include"Galaxy.h"
#include"WButton.h"

class MainMenu
{
private:
	Font font;
	Vector2u windowBounds;

public:
	MainMenu();
	virtual ~MainMenu();

	//Init
	void initBackground();
	void initButtons();
	void initialize(Vector2u &windowBounds);

	//Update
	void updateBackground(Vector2f &mPos, const float &dt);
	void updateButtons(Vector2f &mPos, const float &dt);
	void update(Vector2f &mPos, const float &dt);

	//Draw
	void drawBackground(RenderTarget &target);
	void drawButtons(RenderTarget &target);
	void draw(RenderTarget &target);

	dArr<WButton> buttons;

	//Static
	enum buttons { NORMAL_MODE_BTN = 0, SURVIVAL_MODE_BTN, EXIT_BTN };

};

