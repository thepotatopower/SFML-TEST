#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class key
{
public:
	key()
	{
	}
	virtual ~key();
	sf::Texture keytexture;
	sf::Sprite keys;
	bool collected;
	void picture(sf::RenderWindow &window)
	{
		keytexture.loadFromFile("key_items_sprite_by_aniahmator-dakyghu.png");
		keys.setTexture(keytexture);
		keys.setPosition(sf::Vector2f(400, 400)); // change coordinates to where we want
		keys.scale(sf::Vector2f(.3,.3)); // idk our scale
		collected = false;
	}
	//void Collected();
};