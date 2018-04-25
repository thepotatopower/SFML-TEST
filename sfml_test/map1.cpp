#pragma once
#include "map1.h"
#include "master_map.h"

map1::map1(sf::Vector2u window) : master_map(window)
{

}

bool map1::load_map(sf::RenderWindow &window)
{
	if (!texture1.loadFromFile("maps.png"))
		return 0;
	else
	{
		TextureSize = texture1.getSize();
		WindowSize = window.getSize();

		float Scalex = (float)WindowSize.x / TextureSize.x;
		float Scaley = (float)WindowSize.y / TextureSize.y;

		background.setTexture(texture1);
		background.setScale(Scalex, Scaley*.95);
		set_staircase_bounds(window);
	}
	return 1;
}

void map1::set_staircase_bounds(sf::RenderWindow &window)
{
	this->staircase_next = Rec (*(new sf::Vector2f(window.getSize().x*.05, window.getSize().y*0.93)),
		sf::Color::Green,
		*(new sf::Vector2f(window.getSize().x*0.10, window.getSize().y*0.07)));
}

void map1::door_next(sf::RenderWindow &window)
{
	this->door = Rec(*(new sf::Vector2f(window.getSize().x*.50, window.getSize().y*0.20)),
		sf::Color::Green,
		*(new sf::Vector2f(window.getSize().x, window.getSize().y)));
}