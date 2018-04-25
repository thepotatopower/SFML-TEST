#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "gSprite.h"
#include "Rectangle.h"
#include "map1.h"
#include <iostream>
#include "master_map.h"
#include "map2.h"
#include <thread>
#include <mutex>
#include "Menu.h"
#include "key.h"
#include "map3.h"


using std::cout;

int main()
{
	sf::Music music;
	sf::Text text;
	music.openFromFile("mainmenu2.ogg");
	music.play();

	if (!Menu())
		return 0;

	bool staircase = false; // for going to map 2
	bool map1_door = false; //for going to map 3
							// Create the main window
	bool key_check = false;

	music.openFromFile("Game2.ogg");
	music.play();

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 700), "SFML window");
	sf::Vector2u borders(window.getSize().x, window.getSize().y);

	master_map border(borders);

	map1 map_one(borders);
	map_one.load_map(window); // loads map image

	map2 map_two(borders);
	map_two.load_map(window);

	map3 map_three(borders);
	map_three.load_map(window);

	// Load a sprite to display
	sf::Texture texture, texture2;
	if (!texture.loadFromFile("thelegendofzeldalinktothepast_link_sheet.png"))
		return EXIT_FAILURE;
	texture2.loadFromFile("enemyorignal.png");

	//initialize sprites
	gSprite sprite1(23, 23, texture), sprite2(30, 60, texture);
	sprite1.sprite.setTextureRect(sf::IntRect(0, 0, 23, 23));
	sprite1.sprite.setPosition(380, 50);
	sprite1.hitbox.setSize(sf::Vector2f(16, 22));
	sprite1.hitbox.setFillColor(sf::Color::Green);
	sprite1.hitbox.setPosition(0, 0);
	sprite2.sprite.setTextureRect(sf::IntRect(355, 212, 30, 60));
	sprite2.sprite.setPosition(100, 100);
	
	gSprite enemy1(28, 31, texture2), enemy2(28, 31, texture2);
	enemy1.sprite.setTextureRect(sf::IntRect(194, 0, 28, 31));
	enemy2.sprite.setTextureRect(sf::IntRect(194, 0, 28, 31));

	Spawn baddies;
	baddies.sprite1 = &enemy1;
	baddies.sprite2 = &enemy2;

	key key;
	/////////

	sf::Keyboard keyboard;
	sf::View view;
	sf::Clock clock;
	
	bool freeMove = 1, clock_start = 0, attacking = 0, eliminated = 0, enemy_music;
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
		}

		if (sf::Keyboard::isKeyPressed)
		{
			if (sprite1.freeMove) //only move if freeMove is true
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					sprite1.atkInit(orientation);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					orientation = 's';
					sprite1.orientation = 's';
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						sprite1.atkInit(orientation);
					}
					if (!hitInd(sprite1, border.bottom_barrier, orientation))
					{
						if (elapsed <= 200)
							sprite1.sprite.setTextureRect(sf::IntRect(0, 0, 23, 23)); //change sprite according to direction
						else if (elapsed > 200 && elapsed <= 400)
							sprite1.sprite.setTextureRect(sf::IntRect(0, 29, 23, 23));
						else if (elapsed > 400 && elapsed <= 600)
							sprite1.sprite.setTextureRect(sf::IntRect(30, 29, 23, 23));
						else if (elapsed > 600 && elapsed <= 800)
							sprite1.sprite.setTextureRect(sf::IntRect(60, 29, 23, 23));
						else if (elapsed > 800 && elapsed <= 1000)
							sprite1.sprite.setTextureRect(sf::IntRect(90, 29, 23, 23));
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(0, .1));
						sprite1.sprite.move(sf::Vector2f(0, .1));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					orientation = 'w';
					sprite1.orientation = 'w';
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						sprite1.atkInit(orientation);
					}
					if (!hitInd(sprite1, border.top_barrier, orientation))
					{
						orientation = 'w';
						if (elapsed <= 200)
							sprite1.sprite.setTextureRect(sf::IntRect(89, 118, 23, 23));
						else if (elapsed > 200 && elapsed <= 400)
							sprite1.sprite.setTextureRect(sf::IntRect(119, 118, 23, 23));
						else if (elapsed > 400 && elapsed <= 600)
							sprite1.sprite.setTextureRect(sf::IntRect(149, 118, 23, 23));
						else if (elapsed > 600 && elapsed <= 800)
							sprite1.sprite.setTextureRect(sf::IntRect(179, 118, 23, 23));
						else if (elapsed > 800 && elapsed <= 1000)
							sprite1.sprite.setTextureRect(sf::IntRect(209, 118, 23, 23));
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(0, -.1));
						sprite1.sprite.move(sf::Vector2f(0, -.1));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					orientation = 'a';
					sprite1.orientation = 'a';
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						sprite1.atkInit(orientation);
					}
					if (!hitInd(sprite1, border.right_barrier, orientation))
					{
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
					orientation = 'd';
					sprite1.orientation = 'd';
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						sprite1.atkInit(orientation);
					}
					if (!hitInd(sprite1, border.left_barrier, orientation))
					{
						if (elapsed <= 200) //change sprite animation in accordance to how much time has passed since button has been pressed
							sprite1.sprite.setTextureRect(sf::IntRect(358, 118, 23, 23));
						else if (elapsed > 200 && elapsed <= 400)
							sprite1.sprite.setTextureRect(sf::IntRect(298, 118, 23, 23));
						else if (elapsed > 400 && elapsed <= 600)
							sprite1.sprite.setTextureRect(sf::IntRect(268, 118, 23, 23));
						else if (elapsed > 600 && elapsed <= 800)
							sprite1.sprite.setTextureRect(sf::IntRect(238, 118, 23, 23));
						else if (elapsed > 800 && elapsed <= 1000)
							sprite1.sprite.setTextureRect(sf::IntRect(388, 118, 23, 23));
						if (hitInd(sprite1, sprite2, orientation))
							sprite2.sprite.move(sf::Vector2f(.1, 0));
						sprite1.sprite.move(sf::Vector2f(.1, 0));
					}
				}
			}
			else
			{
				clock.restart();
				clock_start = 0; //end clock if button is released
			}
			if (sprite1.attacking)
			{
				if (hitInd(sprite2, sprite1.hitbox))
				{
					sprite2.atkRec(orientation, &border);
				}
				if (hitInd(enemy1, sprite1.hitbox))
				{
					enemy1.atkRec(orientation, &border);
				}
				if (hitInd(enemy2, sprite1.hitbox))
				{
					enemy2.atkRec(orientation, &border);
				}
			}
			if (hitInd(enemy1, sprite1))
			{
				sprite1.atkRec(enemy1.orientation, &border);
			}
			if (hitInd(enemy2, sprite1))
			{
				sprite1.atkRec(enemy2.orientation, &border);
			}
		}
		// Clear screen
		window.clear();
		// Draw the sprite

		if (!(baddies.alive))
		{
			if (hitInd(sprite1, map_one.staircase_next, orientation)) // sets to map 2
			{
				staircase = true;
				sprite1.sprite.setPosition(380, 50); // puts sprite back in original positon
			}
			if (key_check == true && staircase == false)
			{
				if (hitInd(sprite1, map_one.door, orientation)) // sets to map 3
				{
					staircase = false;
					map1_door = true;
					sprite1.sprite.setPosition(100, 600); //set position somewhere near the staircase of map 2
					music.openFromFile("03 Manabu Namiki, Noriyuki Kamikura - Gentle Breeze.ogg");
					music.play();
				}
				if (hitInd(sprite1, map_one.staircase_next, orientation))
				{
					map1_door = false;
					sprite1.sprite.setPosition(380, 50);
				}
			}
		}
		if (staircase == true) // stays on map 2
		{
			window.draw(map_two.background);
			if (key_check == false && hitInd(sprite1, key))
			{
				key_check = true;
				key.sprite.setPosition(sf::Vector2f(15, 658));
				text.setString("DEMO OVER");
				text.setColor(sf::Color::Red);
				text.setCharacterSize(30);
				text.setPosition(window.getSize().x * .4, window.getSize().y * .4);
				std::thread(spawn, &sprite1, &baddies, &music).detach();
				music.openFromFile("25 Wave Battle.ogg");
				music.play();
			}
			if (!baddies.alive)
			{
				if (hitInd(sprite1, map_one.door, orientation)) //move to map 1
				{
					staircase = false;
					sprite1.sprite.setPosition(100, 600); //set position somewhere near the staircase of map 2
				}
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

		if (baddies.alive)
		{
			window.draw(enemy1.sprite);
			window.draw(enemy2.sprite);
		}
		if (staircase == true) //either draw key only when map2 is active, or when key is collected
			window.draw(key.sprite);
		else if (key_check == true)
			window.draw(key.sprite);
		window.draw(sprite1.sprite);
		window.draw(sprite2.sprite);
		window.draw(text);
		window.display();
	}
	return EXIT_SUCCESS;
}