#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "gSprite.h"
#include "Rectangle.h"
#include "map1.h"
#include <iostream>
#include "master_map.h"
using std::cout;
int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	sf::Vector2u borders(window.getSize().x, window.getSize().y);

	master_map border(borders);
	map1 map_one(borders);
	map_one.load_map(window); // loads map image
	//map_one.set_staircase_bounds(borders); // sets the staircase rec

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("thelegendofzeldalinktothepast_link_sheet.png"))
		return EXIT_FAILURE;

	sf::Image image;
	if (!image.loadFromFile("map2.png"))
	{
		return EXIT_FAILURE;
	}

	// creating hitbox for going to next map
	//Rec staircase_next(*(new sf::Vector2f(window.getSize().x*.05, window.getSize().y*0.93)),
	//	sf::Color::Green,
	//	*(new sf::Vector2f(window.getSize().x*0.10, window.getSize().y*0.07)));
	Rec attack(sf::Vector2f(14, 22), 
		sf::Color::Transparent,
		sf::Vector2f(0, 0));
	/////////////////

	//initialize sprites
	gSprite sprite1(23, 23, texture), sprite2(30, 60, texture);
	sprite1.sprite.setTextureRect(sf::IntRect(0, 0, 23, 23));
	sprite1.sprite.setPosition(380, 50);
	sprite2.sprite.setTextureRect(sf::IntRect(355, 212, 30, 60));
	sprite2.sprite.setPosition(100, 100);
	/////////


	sf::Keyboard keyboard;
	sf::View view;
	sf::Clock clock;

	bool freeMove = 1, clock_start = 0, attacking = 0;
	float x, y;
	double elapsed = 0;
	char orientation = 0; //'w' is up, 'a' is left, 's' is down, 'd' is right

	/*view.reset(sf::FloatRect(0, 0, 800, 600));
	view.setSize(800, 600);
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));*/
	//creating background END
	while (window.isOpen())
	{
	/*	float Scalex = (float)WindowSize.x / TextureSize.x;
		float Scaley = (float)WindowSize.y / TextureSize.y;*/
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
			if (!attacking && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //attack button
			{
				attacking = 1;
				freeMove = 0;
				//if (sprite1.sprite.getTextureRect().left == 0)

			}
			if (attacking && !clock_start)
			{
				clock_start = 1;
				
			}

		}
		//if (hitInd(sprite1, staircase_next, orientation)) // puts you to next level when you hit the stairs
		//{
		//	map_one.texture1.update(image); // updates the map
		//	sprite1.sprite.setPosition(380, 50); // puts sprite back in original positon
		//}

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
						if (hitInd(sprite1, sprite2, 's'))
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
						if (hitInd(sprite1, sprite2, 'w'))
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
						if (hitInd(sprite1, sprite2, 'a'))
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
						if (hitInd(sprite1, sprite2, 'd'))
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
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(map_one.background); // draws the background
		window.draw(sprite1.sprite);
		window.draw(sprite2.sprite);
		window.draw(map_one.staircase_next);
		window.draw(border.top_barrier);
		window.draw(border.bottom_barrier);
		window.draw(border.right_barrier);
		window.draw(border.left_barrier);
		//// Draw the string
		//window.draw(text);
		// Update the window
		//window.setView(view);
		window.display();
	}
	return EXIT_SUCCESS;
}