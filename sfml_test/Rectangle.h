#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Rec : public sf::RectangleShape // used for the next level hit box
{
public:

	Rec()
	{

	}

	Rec(sf::Vector2f &pos, const sf::Color &c, sf::Vector2f &size)
	{
		this->setFillColor(c);
		this->setSize(size);
		this->setPosition(pos);
	}
};