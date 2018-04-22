#pragma once

#include <SFML/Graphics.hpp>

class Rec : public sf::RectangleShape // used for the next level hit box
{
public:
	Rec(sf::Vector2f &pos, const sf::Color &c, sf::Vector2f &size)
	{
		this->setFillColor(c);
		this->setSize(size);
		this->setPosition(pos);
	}
};