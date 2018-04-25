#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "key.h"
using sf::Sprite;

//copy constructor not complete, do not initialize gSprite without intializing its values
class gSprite : public key
{
public:
	gSprite(void);
	gSprite(const gSprite &sprite);
	gSprite(int width, int height, sf::Texture &texture);
	int height;
	int width;
	bool attacking = 0;
	bool attacked = 0;
	bool freeMove = 1;
	Sprite sprite;
};

bool hitInd(const gSprite &sprite1, const gSprite &sprite2, char direction); //'w' for up, 'a' for left, 's' for down, 'd' for right
bool hitInd(gSprite sprite, sf::RectangleShape rec, char direction);
bool hitInd(gSprite sprite, sf::RectangleShape rec);
void atkAnimate(gSprite &sprite);