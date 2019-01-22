#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

//Init
void MainMenu::initBackground()
{

}

void MainMenu::initButtons()
{
	//Create buttons

	//Normal mode button
	this->buttons.add(
		WButton(
			NORMAL_MODE_BTN,
			this->font,
			"Normal",
			12,
			Vector2f(0.f, 0.f),
			0
		)
	);

	//Survival mode button
	this->buttons.add(
		WButton(
			SURVIVAL_MODE_BTN,
			this->font,
			"Survival",
			12,
			Vector2f(0.f, 0.f),
			0
		)
	);

	//Exit button
	this->buttons.add(
		WButton(
			EXIT_BTN,
			this->font,
			"EXIT TO WINDOWS",
			12,
			Vector2f(0.f, 0.f),
			0
		)
	);
}

void MainMenu::initialize(Vector2u &windowBounds)
{
	//Init variables
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
	this->windowBounds = windowBounds;

	//Init background
	this->initBackground();

	//Init buttons
	this->initButtons();
}

//Update
void MainMenu::updateBackground(Vector2f &mPos, const float &dt)
{

}

void MainMenu::updateButtons(Vector2f &mPos, const float &dt)
{
	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i].update(mPos);
	}
}

void MainMenu::update(Vector2f &mPos, const float &dt)
{
	//Update background
	this->updateBackground(mPos, dt);

	//Update buttons
	this->updateButtons(mPos, dt);
}

//Draw
void MainMenu::drawBackground(RenderTarget &target)
{

}

void MainMenu::drawButtons(RenderTarget &target)
{
	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i].draw(target);
	}
}

void MainMenu::draw(RenderTarget &target)
{
	//Draw the background
	this->drawBackground(target);

	//Draw the buttons
	this->drawButtons(target);
}
