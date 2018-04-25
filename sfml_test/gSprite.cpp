#pragma once
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

void gSprite::setHeight(double input)
{
	height = input;
}

void gSprite::setWidth(double input)
{
	width = input;
}

void gSprite::atkInit(char orientation)
{
	if (this->freeMove && !this->attacking)
	{
		this->attacking = 1;
		this->freeMove = 0;
		if (orientation == 's')
		{
			this->hitbox.setRotation(270);
			this->hitbox.setPosition(sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y + (2 * this->height)));
		}
		else if (orientation == 'a')
		{
			this->hitbox.setRotation(0);
			this->hitbox.setPosition(sf::Vector2f(this->sprite.getPosition().x - this->width, this->sprite.getPosition().y));
		}
		else if (orientation == 'd')
		{
			this->hitbox.setRotation(0);
			this->hitbox.setPosition(sf::Vector2f(this->sprite.getPosition().x + this->width, this->sprite.getPosition().y));
		}
		else if (orientation == 'w')
		{
			this->hitbox.setRotation(270);
			this->hitbox.setPosition(sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y));
		}

		std::thread(&atkAnimate, this).detach();
	}
}

void gSprite::atkRec(char orientation, master_map *border)
{
	if (!(this->attacked))
	{
		std::thread(&atkd, this, orientation, border).detach();
	}
}

void atkd(gSprite *sprite, char orientation, master_map *map)
{
	sprite->attacked = 1;
	sprite->freeMove = 0;
	sf::Clock clock;
	double elapsed = clock.getElapsedTime().asMilliseconds();
	while (elapsed < 1000)
	{
		elapsed = clock.getElapsedTime().asMilliseconds();
		if (!hitInd(*sprite, map->bottom_barrier) &&
			!hitInd(*sprite, map->top_barrier) &&
			!hitInd(*sprite, map->left_barrier) &&
			!hitInd(*sprite, map->right_barrier))
		{
			if (orientation == 's')
				sprite->sprite.move(sf::Vector2f(0, .0000001 * (1000 - elapsed)));
			else if (orientation == 'w')
				sprite->sprite.move(sf::Vector2f(0, -.0000001 * (1000 - elapsed)));
			else if (orientation == 'a')
				sprite->sprite.move(sf::Vector2f(-.0000001 * (1000 - elapsed), 0));
			else if (orientation == 'd')
				sprite->sprite.move(sf::Vector2f(.0000001 * (1000 - elapsed), 0));
		}
		else
			std::cout << "hit" << std::endl;
	}
	sprite->attacked = 0;
	sprite->freeMove = 1;
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

bool hitInd(const gSprite &sprite, const sf::RectangleShape &rec)
{
	if (sprite.sprite.getPosition().x >= rec.getPosition().x - sprite.width &&
		sprite.sprite.getPosition().x <= rec.getPosition().x + sprite.width &&
		sprite.sprite.getPosition().y >= rec.getPosition().y - sprite.height &&
		sprite.sprite.getPosition().y <= rec.getPosition().y + sprite.height)
		return true;
	else
		return false;
}

bool hitInd(const gSprite &sprite, const gSprite &sprite2)
{
	if (sprite.sprite.getPosition().x >= sprite2.sprite.getPosition().x - sprite.width &&
		sprite.sprite.getPosition().x <= sprite2.sprite.getPosition().x + sprite.width &&
		sprite.sprite.getPosition().y >= sprite2.sprite.getPosition().y - sprite.height &&
		sprite.sprite.getPosition().y <= sprite2.sprite.getPosition().y + sprite.height)
		return true;
	else
		return false;
}

void atkAnimate(gSprite *sprite)
{
	sf::Clock clock;
	double elapsed = clock.getElapsedTime().asMilliseconds();
	std::cout << elapsed;
	while (elapsed < 500)
	{
		elapsed = clock.getElapsedTime().asMilliseconds();
	}
	sprite->attacking = 0;
	sprite->freeMove = 1;
}

char reverse(char orientation)
{
	if (orientation == 's')
		return 'w';
	else if (orientation == 'w')
		return 's';
	else if (orientation == 'a')
		return 'd';
	else if (orientation == 'd')
		return 'a';
}