#include "TextTag.h"

TextTag::TextTag(Font *font, std::string text,
	const Color color,
	Vector2f position, Vector2f direction,
	unsigned int size, float timerMax,
	bool accelerate)
{
	this->dtMultiplier = 62.5f;

	this->text.setFont(*font);
	this->text.setCharacterSize(size);
	this->text.setPosition(position);
	this->text.setString(text);
	this->text.setColor(color);

	this->speed = 2.f;
	this->direction.x = direction.x;
	this->direction.y = direction.y;
	this->timerMax = timerMax;
	this->timer = this->timerMax;
	this->accelerate = accelerate;
}

TextTag::~TextTag()
{

}

void TextTag::Update(const float &dt)
{
	//Update timer
	if (this->timer > 0.f)
	{
		this->timer -= 1.f * dt * this->dtMultiplier;

		if (this->accelerate)
		{
			if (this->timer > this->timerMax / 2)
			{
				this->text.move(this->direction.x * (this->speed*5.f) * dt * this->dtMultiplier,
					this->direction.y * (this->speed*5.f) * dt * this->dtMultiplier);
			}
			else
			{
				this->text.move(this->direction.x * this->speed * dt * this->dtMultiplier,
					this->direction.y * this->speed * dt * this->dtMultiplier);
			}
		}
		else
		{
			this->text.move(this->direction.x * this->speed * dt * this->dtMultiplier,
				this->direction.y * this->speed * dt * this->dtMultiplier);
		}	
	}
	else
	{
		this->text.setFillColor(Color(0, 0, 0, 0));
	}
}

void TextTag::Draw(RenderTarget &target)
{
	target.draw(this->text);
}