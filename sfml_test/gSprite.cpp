#include "gSprite.h"

gSprite::gSprite(void)
{
	height = 0;
	width = 0;
}

gSprite::gSprite(const gSprite &sprite)
{
	this->height = sprite.height;
	this->width = sprite.width;
	this->sprite = sprite.sprite;
}

gSprite::gSprite(int width, int height, sf::Texture &texture)
{
	this->height = height;
	this->width = width;
	this->sprite.setTexture(texture);
}

//function for determining if sprite1 has hit sprite2, returns 1 if hit, 0 if not
//direction is the direction sprite1 is moving
//'w' for up, 'a' for left, 's' for down, 'd' for right
bool hitInd(gSprite sprite1, gSprite sprite2, char direction)
{
	bool hit = 0;
	if (direction == 'w') //up, checks if sprite1 hits bottom of sprite2
	{
		if (sprite1.sprite.getPosition().y <= sprite2.sprite.getPosition().y + sprite2.height + 1 &&
			sprite1.sprite.getPosition().y > sprite2.sprite.getPosition().y &&
			//!hitInd(sprite1, sprite2, 'a') && !hitInd(sprite1, sprite2, 'd') &&
			sprite1.sprite.getPosition().x > sprite2.sprite.getPosition().x - sprite1.width &&
			sprite1.sprite.getPosition().x < sprite2.sprite.getPosition().x + sprite2.width)
			hit = 1;
	}
	else if (direction == 'a') //left, checks if sprite1 hits right of sprite2
	{
		if (sprite1.sprite.getPosition().x > sprite2.sprite.getPosition().x &&
			sprite1.sprite.getPosition().x <= sprite2.sprite.getPosition().x + sprite2.width + 1 &&
		//	!hitInd(sprite1, sprite2, 'w') && !hitInd(sprite1, sprite2, 's') &&
			sprite1.sprite.getPosition().y > sprite2.sprite.getPosition().y - sprite1.height &&
			sprite1.sprite.getPosition().y < sprite2.sprite.getPosition().y + sprite2.height)
			hit = 1;
	}
	else if (direction == 's') //down, checks if sprite1 hits top of sprite2
	{
		if (sprite1.sprite.getPosition().y >= sprite2.sprite.getPosition().y - sprite1.height - 1 &&
			sprite1.sprite.getPosition().y < sprite2.sprite.getPosition().y &&
		//	!hitInd(sprite1, sprite2, 'a') && !hitInd(sprite1, sprite2, 'd') &&
			sprite1.sprite.getPosition().x > sprite2.sprite.getPosition().x - sprite1.width &&
			sprite1.sprite.getPosition().x < sprite2.sprite.getPosition().x + sprite2.width)
			hit = 1;
	}
	else if (direction == 'd') //right, checks if sprite1 hits left of sprite2
	{
		if (sprite1.sprite.getPosition().x < sprite2.sprite.getPosition().x &&
			sprite1.sprite.getPosition().x >= sprite2.sprite.getPosition().x - sprite1.width - 1 &&
			sprite1.sprite.getPosition().y > sprite2.sprite.getPosition().y - sprite1.height &&
			sprite1.sprite.getPosition().y < sprite2.sprite.getPosition().y + sprite2.height)
			hit = 1;
	}
	return hit;
}

bool hitInd(gSprite sprite, sf::RectangleShape rec, char direction)
{
	bool hit = 0;
	if (direction == 'w') //up, checks if sprite hits bottom of rec
	{
		if (sprite.sprite.getPosition().y <= rec.getPosition().y + rec.getSize().y + 1 &&
			sprite.sprite.getPosition().y > rec.getPosition().y &&
			//!hitInd(sprite, rec, 'a') && !hitInd(sprite, rec, 'd') &&
			sprite.sprite.getPosition().x > rec.getPosition().x - sprite.width &&
			sprite.sprite.getPosition().x < rec.getPosition().x + rec.getSize().x)
			hit = 1;
	}
	else if (direction == 'a') //left, checks if sprite hits right of rec
	{
		if (sprite.sprite.getPosition().x > rec.getPosition().x &&
			sprite.sprite.getPosition().x <= rec.getPosition().x + rec.getSize().x + 1 &&
			//	!hitInd(sprite, rec, 'w') && !hitInd(sprite, rec, 's') &&
			sprite.sprite.getPosition().y > rec.getPosition().y - sprite.height &&
			sprite.sprite.getPosition().y < rec.getPosition().y + rec.getSize().y)
			hit = 1;
	}
	else if (direction == 's') //down, checks if sprite hits top of rec
	{
		if (sprite.sprite.getPosition().y >= rec.getPosition().y - sprite.height - 1 &&
			sprite.sprite.getPosition().y < rec.getPosition().y &&
			//	!hitInd(sprite, rec, 'a') && !hitInd(sprite, rec, 'd') &&
			sprite.sprite.getPosition().x > rec.getPosition().x - sprite.width &&
			sprite.sprite.getPosition().x < rec.getPosition().x + rec.getSize().x)
			hit = 1;
	}
	else if (direction == 'd') //right, checks if sprite hits left of rec
	{
		if (sprite.sprite.getPosition().x < rec.getPosition().x &&
			sprite.sprite.getPosition().x >= rec.getPosition().x - sprite.width - 1 &&
			sprite.sprite.getPosition().y > rec.getPosition().y - sprite.height &&
			sprite.sprite.getPosition().y < rec.getPosition().y + rec.getSize().y)
			hit = 1;
	}
	return hit;
}

bool hitInd(gSprite sprite, sf::RectangleShape rec)
{
	if (sprite.sprite.getPosition().x >= rec.getPosition().x - sprite.width &&
		sprite.sprite.getPosition().x <= rec.getPosition().x + sprite.width &&
		sprite.sprite.getPosition().y >= rec.getPosition().y - sprite.height &&
		sprite.sprite.getPosition().y <= rec.getPosition().y + sprite.height)
		return true;
	else
		return false;
}

void atkAnimate(gSprite &sprite)
{
	sf::Clock clock;
	while (clock.getElapsedTime().asMilliseconds() > 500)
	{

	}
	sprite.attacking = 0;
	sprite.freeMove = 1;
}