#pragma once
#include "master_map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class map3 : public master_map
{
public:
	map3(sf::Vector2u window);

	bool load_map(sf::RenderWindow &window);

	sf::Sprite background;
	sf::Vector2u TextureSize;
	sf::Vector2u WindowSize;
	sf::Texture texture1;
};