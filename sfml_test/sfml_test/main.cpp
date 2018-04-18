#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("thelegendofzeldalinktothepast_link_sheet.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture), sprite2(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 23, 23));
	sprite2.setTextureRect(sf::IntRect(355, 212, 30, 60));
	sprite2.setPosition(100, 100);
	sf::Keyboard keyboard;
	sf::View view;
	bool pressed = 0, clock_start = 0;
	sf::Clock clock;
	float x, y;
	double elapsed = 0;
	// Create a graphical text to display
	//sf::Font font;
	//if (!font.loadFromFile("arial.ttf"))
	//	return EXIT_FAILURE;
	//sf::Text text("Hello SFML", font, 50);
	//// Load a music to play
	//sf::Music music;
	//if (!music.openFromFile("nice_music.ogg"))
	//	return EXIT_FAILURE;
	//// Play the music
	//music.play();
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed)
		{
			if (!clock_start)
			{
				clock.restart();
				clock_start = 1;
			}
			elapsed = clock.getElapsedTime().asMilliseconds();
			if (elapsed > 1000)
			{
				clock.restart();
				elapsed = clock.getElapsedTime().asMilliseconds();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sprite.setTextureRect(sf::IntRect(0, 0, 23, 23));
				if (!(sprite.getPosition().y == sprite2.getPosition().y + 23
					&& (sprite.getPosition().x == sprite2.getPosition().x + 23
						&& sprite.getPosition().x == sprite2.getPosition().x - 23)))
					sprite2.move(sf::Vector2f(0, .1));
				sprite.move(sf::Vector2f(0, .1));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sprite.setTextureRect(sf::IntRect(89, 118, 23, 23));
				if (!(sprite.getPosition().y == sprite2.getPosition().y - 23
					&& (sprite.getPosition().x == sprite2.getPosition().x + 23
						&& sprite.getPosition().x == sprite2.getPosition().x - 23)))
					sprite2.move(sf::Vector2f(0, -.1));
				sprite.move(sf::Vector2f(0, -.1));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (elapsed <= 200)
					sprite.setTextureRect(sf::IntRect(358, 28, 23, 23));
				else if (elapsed > 200 && elapsed <= 400)
					sprite.setTextureRect(sf::IntRect(298, 28, 23, 23));
				else if (elapsed > 400 && elapsed <= 600)
					sprite.setTextureRect(sf::IntRect(268, 28, 23, 23));
				else if (elapsed > 600 && elapsed <= 800)
					sprite.setTextureRect(sf::IntRect(238, 28, 23, 23));
				else if (elapsed > 800 && elapsed <= 1000)
					sprite.setTextureRect(sf::IntRect(388, 28, 23, 23));
				if (!(sprite.getPosition().x == sprite2.getPosition().x + 23
					&& (sprite.getPosition().y == sprite2.getPosition().y + 23
						&& sprite.getPosition().y == sprite2.getPosition().y - 23)))
					sprite2.move(sf::Vector2f(-.1, 0));
				sprite.move(sf::Vector2f(-.1, 0));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				sprite.setTextureRect(sf::IntRect(328, 128, 23, 23));
				if (!(sprite.getPosition().x == sprite2.getPosition().x - 23
					&& (sprite.getPosition().y == sprite2.getPosition().y + 23
						&& sprite.getPosition().y == sprite2.getPosition().y - 23)))
					sprite2.move(sf::Vector2f(.1, 0));
				sprite.move(sf::Vector2f(.1, 0));
			}
		}
		else
		{
			clock.restart();
			clock_start = 0;
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(sprite);
		window.draw(sprite2);
		//// Draw the string
		//window.draw(text);
		// Update the window
		view.zoom(0.5f);
		window.display();
	}
	return EXIT_SUCCESS;
}