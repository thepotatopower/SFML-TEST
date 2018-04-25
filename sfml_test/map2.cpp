#pragma once
#include "map2.h"
map2::map2(sf::Vector2u window) : master_map(window)
{

}

bool map2::load_map(sf::RenderWindow &window)
{
	if (!texture1.loadFromFile("map2.png"))
		return 0;
	else
	{
		TextureSize = texture1.getSize();
		WindowSize = window.getSize();

		float Scalex = (float)WindowSize.x / TextureSize.x;
		float Scaley = (float)WindowSize.y / TextureSize.y;

		background.setTexture(texture1);
		background.setScale(Scalex, Scaley*.95);
	}
	return 1;
}

void map2::door_next(sf::RenderWindow &window)
{
	this->door = Rec(*(new sf::Vector2f(window.getSize().x*.50, window.getSize().y*0.20)),
		sf::Color::Green,
		*(new sf::Vector2f(window.getSize().x, window.getSize().y)));
}