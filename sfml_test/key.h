#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "gSprite.h"
class key : public gSprite
{
public:
	key()
	{
		if (!keytexture.loadFromFile("key_items_sprite_by_aniahmator-dakyghu.png"))
			std::cout << "failed" << std::endl;
		((gSprite *)this)->sprite.setTexture(keytexture);
		((gSprite *)this)->sprite.setPosition(sf::Vector2f(400, 400)); // change coordinates to where we want
		((gSprite *)this)->sprite.scale(sf::Vector2f(.3, .3)); // idk our scale

		collected = false;
	}
	virtual ~key();
	sf::Texture keytexture;
	bool collected;
	//void Collected();
};