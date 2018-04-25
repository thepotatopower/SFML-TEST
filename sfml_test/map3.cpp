#pragma once
#include "map3.h"
#include "master_map.h"

map3::map3(sf::Vector2u window) : master_map(window)
{

}

bool map3::load_map(sf::RenderWindow &window)
{
	if (!texture1.loadFromFile("map3.png"))
		return 0;
	else
	{
		TextureSize = texture1.getSize();
		WindowSize = window.getSize();

		float Scalex = (float)WindowSize.x / TextureSize.x;
		float Scaley = (float)WindowSize.y / TextureSize.y;

		background.setTexture(texture1);
		background.setScale(Scalex, Scaley*.95);
		//set_staircase_bounds(window);
	}
	return 1;
}
