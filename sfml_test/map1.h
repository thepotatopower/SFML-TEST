#pragma once
#include "master_map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class map1 : public master_map
{
public:
	map1(sf::Vector2u window);

	bool load_map(sf::RenderWindow &window);

	void set_staircase_bounds(sf::RenderWindow &window);

	void door_next(sf::RenderWindow &window);

	sf::Sprite background;
	sf::Vector2u TextureSize;
	sf::Vector2u WindowSize;
	sf::Texture texture1;

	Rec staircase_next;
	Rec door;
};