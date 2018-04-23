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

gSprite::gSprite(int height, int width, sf::Texture &texture)
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
	if (direction == 'w')
	{
		if (sprite1.sprite.getPosition().y <= sprite2.sprite.getPosition().y &&
			sprite1.sprite.getPosition().x < sprite2.sprite.getPosition().x - sprite1.width &&
			sprite1.sprite.getPosition().x > sprite2.sprite.getPosition().x + sprite1.width)
			hit = 1;
	}
	else if (direction == 'a')
	{
		if (sprite1.sprite.getPosition().x <= sprite2.sprite.getPosition().x + sprite2.width &&
			sprite1.sprite.getPosition().y > sprite2.sprite.getPosition().y - sprite1.height &&
			sprite1.sprite.getPosition().y < sprite2.sprite.getPosition().y + sprite1.height)
			hit = 1;
	}
	else if (direction == 's')
	{
		if (sprite1.sprite.getPosition().y >= sprite2.sprite.getPosition().y - sprite2.height &&
			sprite1.sprite.getPosition().x < sprite2.sprite.getPosition().x - sprite1.width &&
			sprite1.sprite.getPosition().x > sprite2.sprite.getPosition().x + sprite1.width)
			hit = 1;
	}
	else if (direction == 'd')
	{
		if (sprite1.sprite.getPosition().x >= sprite2.sprite.getPosition().x - sprite2.width &&
			sprite1.sprite.getPosition().y > sprite2.sprite.getPosition().y - sprite1.height &&
			sprite1.sprite.getPosition().y < sprite2.sprite.getPosition().y + sprite1.height)
			hit = 1;
	}
	return hit;
}