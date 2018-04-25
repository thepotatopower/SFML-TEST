#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Rectangle.h"
using sf::Sprite;

//copy constructor not complete, do not initialize gSprite without intializing its values
class gSprite 
{
public:
	gSprite(void);
	gSprite(const gSprite &sprite);
	gSprite(int width, int height, sf::Texture &texture);
	void setHeight(double input);
	void setWidth(double input);
	void atkd(char orientation);
	int height;
	int width;
	bool attacking = 0;
	bool attacked = 0;
	bool freeMove = 1;
	Sprite sprite;
};

bool hitInd(gSprite sprite1, gSprite sprite2, char direction); //'w' for up, 'a' for left, 's' for down, 'd' for right
bool hitInd(gSprite sprite, sf::RectangleShape rec, char direction);
bool hitInd(const gSprite &sprite, const sf::RectangleShape &rec);
void atkAnimate(gSprite *sprite);
char reverse(char orientation);
bool hitInd(const gSprite &sprite, const gSprite &sprite2);
