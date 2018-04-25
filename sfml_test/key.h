#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "gSprite.h"
class key : public gSprite
{
public:
	sf::Texture keytexture;
	sf::Sprite keys;
	bool collected;
	key(sf::RenderWindow &window)
	{
		keytexture.loadFromFile("key_items_sprite_by_aniahmator-dakyghu.png");
		keys.setTexture(keytexture);
		keys.setPosition(sf::Vector2f(20, 20)); // change coordinates to where we want
		keys.scale(sf::Vector2f(.2,.2)); // idk our scale
	}
};