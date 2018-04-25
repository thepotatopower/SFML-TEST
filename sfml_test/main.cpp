#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "key.h"
#include "map1.h"
#include <iostream>
#include "master_map.h"
#include "map2.h"
#include "map3.h"
using std::cout;
int main()
{
	sf::Music music;
	music.openFromFile("mainmenu2.ogg");
	music.play();
	bool staircase = false; // for going to map 2
	bool map1_door = false; //for going to map 3
							// Create the main window
	bool key_check = false;

	sf::RenderWindow window(sf::VideoMode(800, 700), "SFML window");
	sf::Vector2u borders(window.getSize().x, window.getSize().y);

	master_map border(borders);

	//// Key casts to a gsprite for hitbox function
	/*key* keys = new gSprite;
	gSprite* Key = dynamic_cast<gSprite*>(keys);
	Key->picture(window);
	Key->height = Key->keys.getTextureRect().height;
	Key->width = Key->keys.getTextureRect().width;*/
	////

	map1 map_one(borders);
	map_one.load_map(window); // loads map image

	map2 map_two(borders);
	map_two.load_map(window);

	map3 map_three(borders);
	map_three.load_map(window);

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("thelegendofzeldalinktothepast_link_sheet.png"))
		return EXIT_FAILURE;

	sf::RectangleShape attack;
	attack.setSize(sf::Vector2f(16, 22));
	attack.setFillColor(sf::Color::Green);
	attack.setPosition(0, 0);

	//initialize sprites
	gSprite sprite1(23, 23, texture), sprite2(30, 60, texture);
	sprite1.sprite.setTextureRect(sf::IntRect(0, 0, 23, 23));
	sprite1.sprite.setPosition(380, 50);
	sprite2.sprite.setTextureRect(sf::IntRect(355, 212, 30, 60));
	sprite2.sprite.setPosition(100, 100);
	key key;
	////////

	sf::Keyboard keyboard;
	sf::View view;
	sf::Clock clock;

	//sf::Thread atk(&atkAnimate, sprite1);
	bool freeMove = 1, clock_start = 0, attacking = 0;
	float x, y;
	double elapsed = 0;
	char orientation = 's'; //'w' is up, 'a' is left, 's' is down, 'd' is right

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // Closes the game when you click escape
			{
				window.close();
			}
			//if (!attacking && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //attack button
			//{
			//	attacking = 1;
			//	freeMove = 0;
			//	clock.restart();
			//	if (orientation = 's')
			//	{
			//		attack.setRotation(270);
			//		attack.setPosition(sprite1.sprite.getPosition().x, sprite1.sprite.getPosition().y + sprite1.height);
			//	}
			//}
			if (attacking)
			{
				if (clock.getElapsedTime().asMilliseconds() > 1)
				{
					attacking = 0;
					freeMove = 1;
				}
				if (hitInd(sprite1, attack))
				{
					sprite2.sprite.move(0, 5);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed)
		{
			if (freeMove) //only move if freeMove is true
			{
				if (!clock_start) //start clock when key is pressed
				{
					clock.restart();
					clock_start = 1; //set counter to indicate clock has started
				}
				elapsed = clock.getElapsedTime().asMilliseconds();
				if (elapsed > 1000) //measure time in increments of 1000 milliseconds
				{
					clock.restart(); //restart clock if time passes 1000 milliseconds
					elapsed = clock.getElapsedTime().asMilliseconds();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (!hitInd(sprite1, border.bottom_barrier, orientation))
					{
						orientation = 's';
						sprite1.sprite.setTextureRect(sf::IntRect(0, 0, 23, 23)); //change sprite according to direction
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(0, .1));
						sprite1.sprite.move(sf::Vector2f(0, .1));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (!hitInd(sprite1, border.top_barrier, orientation))
					{
						orientation = 'w';
						sprite1.sprite.setTextureRect(sf::IntRect(89, 118, 23, 23));
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(0, -.1));
						sprite1.sprite.move(sf::Vector2f(0, -.1));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (!hitInd(sprite1, border.right_barrier, orientation))
					{
						orientation = 'a';
						if (elapsed <= 200) //change sprite animation in accordance to how much time has passed since button has been pressed
							sprite1.sprite.setTextureRect(sf::IntRect(358, 28, 23, 23));
						else if (elapsed > 200 && elapsed <= 400)
							sprite1.sprite.setTextureRect(sf::IntRect(298, 28, 23, 23));
						else if (elapsed > 400 && elapsed <= 600)
							sprite1.sprite.setTextureRect(sf::IntRect(268, 28, 23, 23));
						else if (elapsed > 600 && elapsed <= 800)
							sprite1.sprite.setTextureRect(sf::IntRect(238, 28, 23, 23));
						else if (elapsed > 800 && elapsed <= 1000)
							sprite1.sprite.setTextureRect(sf::IntRect(388, 28, 23, 23));
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(-.1, 0));
						sprite1.sprite.move(sf::Vector2f(-.1, 0));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (!hitInd(sprite1, border.left_barrier, orientation))
					{
						orientation = 'd';
						sprite1.sprite.setTextureRect(sf::IntRect(328, 118, 23, 23));
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(.1, 0));
						sprite1.sprite.move(sf::Vector2f(.1, 0));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (sprite1.freeMove && !sprite1.attacking)
					{
						sprite1.attacking = 1;
						freeMove = 0;
						clock.restart();
						if (orientation == 's')
						{
							attack.setRotation(0);
							attack.setPosition(sf::Vector2f(sprite1.sprite.getPosition().x, sprite1.sprite.getPosition().y + sprite1.height));
						}
						//					atk.launch();
					}
				}
			}
			else
			{
				clock.restart();
				clock_start = 0; //end clock if button is released
			}
		}
		if (hitInd(sprite1, key))
		{
			key.sprite.setPosition(sf::Vector2f(15, 658));
			key_check = true;
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(attack);
		if (staircase == true) //either draw key only when map2 is active, or when key is collected
			window.draw(key.sprite);
		else if (key_check == true)
			window.draw(key.sprite);
		if (hitInd(sprite1, map_one.staircase_next, orientation)) // sets to map 2
		{
			staircase = true;
			sprite1.sprite.setPosition(380, 50); // puts sprite back in original positon
		}
		if (key_check == true)
		{
			if (hitInd(sprite1, map_one.door, orientation)) // sets to map 3
			{
				staircase = false;
				map1_door = true;
			}
		}
		if (staircase == true) // stays on map 2
		{
			window.draw(map_two.background);
			window.draw(key.sprite);
			if (hitInd(sprite1, map_one.door, orientation)) //i want this to transition back to map 1
			{
				staircase = false;
				sprite1.sprite.setPosition(100, 600); //set position somewhere near the staircase of map 2
			}
		}
		else if (map1_door) // stays on map 3
		{
			window.draw(map_three.background);
		}
		else //stays on map 1
		{
			window.draw(map_one.background);
		}
		window.draw(sprite1.sprite);
		//window.draw(map_two.door);     why is it not drawing this
		window.display();
	}
	return EXIT_SUCCESS;
}