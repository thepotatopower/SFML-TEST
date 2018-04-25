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
	sprite->life--;
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
		if (sprite->orientation == 'a')
		{
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(241, 89, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(266, 89, 28, 28));
			clock.restart();
			while(clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(294, 89, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(326, 89, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(357, 85, 28, 28));
		}
		if (sprite->orientation == 'd') 
		{
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(241, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(266, 178, 28, 28));
			clock.restart();
			while(clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(294, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(326, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(357, 178, 28, 28));
		}
		if (sprite->orientation == 'w')
		{
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(0, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(28, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(59, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(86, 178, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(113, 178, 28, 28));
		}
		if (sprite->orientation == 's')
		{
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(0, 88, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(28, 88, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(59, 88, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(86, 88, 28, 28));
			clock.restart();
			while (clock.getElapsedTime().asMilliseconds() <= 100)
				sprite->sprite.setTextureRect(sf::IntRect(113, 88, 28, 28));
		}
		if (sprite->orientation == 'a')
			sprite->sprite.setTextureRect(sf::IntRect(358, 28, 23, 23));
		else if (sprite->orientation == 's')
			sprite->sprite.setTextureRect(sf::IntRect(0, 0, 23, 23));
	else if (sprite->orientation == 'd')
		sprite->sprite.setTextureRect(sf::IntRect(328, 118, 23, 23));
	else if (sprite->orientation == 'w')
		sprite->sprite.setTextureRect(sf::IntRect(89, 118, 23, 23));
	sprite->freeMove = 1;
	sprite->attacking = 0;
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

void spawn(gSprite* player, Spawn *baddies, sf::Music *music)
{
	sf::Clock clock;
	baddies->alive = 1;
	baddies->sprite1->life = 3;
	baddies->sprite2->life = 3;
	baddies->sprite1->sprite.setPosition(100, 500);
	baddies->sprite1->sprite.setPosition(700, 500);
	while (baddies->sprite1->life > 0 || baddies->sprite2->life > 0)
	{
		if (clock.getElapsedTime().asMilliseconds() % 10 == 0)
		{
			if (baddies->sprite1->life > 0)
			{
				if (baddies->sprite1->freeMove)
				{
					if (player->sprite.getPosition().y > baddies->sprite1->sprite.getPosition().y)
					{
						baddies->sprite1->sprite.move(0, .00025);
						baddies->sprite1->orientation = 's';
					}
					if (player->sprite.getPosition().y < baddies->sprite1->sprite.getPosition().y)
					{
						baddies->sprite1->sprite.move(0, -.00025);
						baddies->sprite1->orientation = 'w';
					}
					if (player->sprite.getPosition().y <= baddies->sprite1->sprite.getPosition().y + 10
						&& player->sprite.getPosition().y >= baddies->sprite1->sprite.getPosition().y - 10)
					{
						if (player->sprite.getPosition().x > baddies->sprite1->sprite.getPosition().x)
						{
							baddies->sprite1->sprite.move(.00025, 0);
							baddies->sprite1->orientation = 'd';
						}
						if (player->sprite.getPosition().x < baddies->sprite1->sprite.getPosition().x)
						{
							baddies->sprite1->sprite.move(-.00025, 0);
							baddies->sprite1->orientation = 'a';
						}
					}
				}
			}
			if (baddies->sprite2->life > 0)
			{
				if (baddies->sprite2->freeMove)
				{
					if (player->sprite.getPosition().y > baddies->sprite2->sprite.getPosition().y)
					{
						baddies->sprite2->sprite.move(0, .0003);
						baddies->sprite2->orientation = 's';
					}
					if (player->sprite.getPosition().y < baddies->sprite2->sprite.getPosition().y)
					{
						baddies->sprite2->sprite.move(0, -.0003);
						baddies->sprite2->orientation = 'w';
					}
					if (player->sprite.getPosition().y <= baddies->sprite2->sprite.getPosition().y + 10
						&& player->sprite.getPosition().y >= baddies->sprite2->sprite.getPosition().y - 10)
					{
						if (player->sprite.getPosition().x > baddies->sprite2->sprite.getPosition().x)
						{
							baddies->sprite2->sprite.move(.0003, 0);
							baddies->sprite2->orientation = 'd';
						}
						if (player->sprite.getPosition().x < baddies->sprite2->sprite.getPosition().x)
						{
							baddies->sprite2->sprite.move(-.0003, 0);
							baddies->sprite2->orientation = 'a';
						}
					}
				}
			}
		}
	}
	baddies->alive = 0;
	music->openFromFile("Game2.ogg");
	music->play();
	baddies->sprite2->sprite.setPosition(1000, 1000);
	baddies->sprite1->sprite.setPosition(1000, 1000);
}