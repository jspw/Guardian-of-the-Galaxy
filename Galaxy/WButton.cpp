#include "WButton.h"

//Static
dArr<Texture> WButton::textures;
int WButton::nrOfTextures;

void WButton::initTextures()
{
	Texture temp;

	temp.loadFromFile("Textures/Buttons/button01.png");
	WButton::textures.add(temp);

	WButton::nrOfTextures = WButton::textures.size();
}

WButton::WButton(
	int id,
	Font &font, 
	std::string text,
	const unsigned int charSize,
	Vector2f pos, 
	int textureIndex
)
{
	this->id = id;

	this->text.setFont(font);
	this->text.setCharacterSize(charSize);
	this->text.setString(text);

	this->colorIdle = Color(200, 200, 200, 240);
	this->colorHover = Color(255, 255, 255, 240);
	this->colorPressed = Color(50, 50, 50, 240);

	this->idle = true;
	this->hover = false;
	this->pressed = false;

	if (textureIndex < 0 || textureIndex >= WButton::nrOfTextures)
		std::cout << "ERROR NO SUCH BUTTON TEXTURE, WBUTTON CONSTRUCTOR." << "\n\n";
	else
		this->sprite.setTexture(WButton::textures[textureIndex]);

	this->sprite.setPosition(pos);
	this->sprite.setColor(this->colorIdle);
	this->text.setPosition(this->sprite.getPosition());
}

WButton::~WButton()
{

}

bool WButton::isPressed()
{
	return this->pressed;
}

bool WButton::isHover()
{
	return this->hover;
}

bool WButton::isIdle()
{
	return this->idle;
}

void WButton::update(Vector2f mousePos)
{
	if (!Mouse::isButtonPressed(Mouse::Left) && !sprite.getGlobalBounds().contains(mousePos))
	{
		this->idle = true;
		this->hover = false;
		this->pressed = false;

		this->sprite.setColor(this->colorIdle);
	}
	if (!Mouse::isButtonPressed(Mouse::Left) && sprite.getGlobalBounds().contains(mousePos))
	{
		this->idle = false;
		this->hover = true;
		this->pressed = false;

		this->sprite.setColor(this->colorHover);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && sprite.getGlobalBounds().contains(mousePos))
	{
		this->idle = false;
		this->hover = false;
		this->pressed = true;

		this->sprite.setColor(this->colorPressed);
	}
}

void WButton::draw(RenderTarget &target)
{
	target.draw(this->sprite);
	target.draw(this->text);
}