#include "Menu.h"

bool Menu()
{
	//Citation:
	//Following code was used.
	//https://www.sfml-dev.org/index.php
	//Following website was referenced.
	//https://gamedev.stackexchange.com/questions/142308/how-to-create-a-button-in-sfml

		//Definitons 
		int USER = 0;
		Texture background, playBox, instructionBox, exitBox, rulesBox, link, key, goblin;
		Sprite backgroundImage, playBoxImage, instructionBoxImage, exitBoxImage, rulesBoxImage,
			linkImage, keyImage, goblinImage;
		Font font;
		Text title, title2, play, instruction, exit, paragraph, paragraph1, paragraph2;
		Event Mouse_Action;
		RenderWindow window(VideoMode(1920, 1080), "Andy's Quest", sf::Style::Default);
		Clock clock;
		bool clock_start = false;
		//Code Start
		//Loads Background
		background.loadFromFile("Menu_Screen.jpg");
		backgroundImage.setTexture(background);
		//Loads Font
		font.loadFromFile("EnchantedLand.otf");
		//Play(Background)
		playBox.loadFromFile("Graybox.png");
		playBoxImage.setPosition(200.0f, 250.0f);
		float playButtonWidth = playBoxImage.getLocalBounds().width;
		float playButtonHeight = playBoxImage.getLocalBounds().height;
		playBoxImage.setTexture(playBox);
		//Instruction(Background)
		instructionBox.loadFromFile("Graybox.png");
		instructionBoxImage.setPosition(200.0f, 400.0f);
		float instructionBoxWidth = instructionBoxImage.getLocalBounds().width;
		float instructionBoxHeight = instructionBoxImage.getLocalBounds().height;
		instructionBoxImage.setTexture(instructionBox);
		//Exit(Background)
		exitBox.loadFromFile("Graybox.png");
		exitBoxImage.setPosition(200.0f, 550.0f);
		float exitBoxWidth = exitBoxImage.getLocalBounds().width;
		float exitBoxHeight = exitBoxImage.getLocalBounds().height;
		exitBoxImage.setTexture(exitBox);
		//Title
		title.setStyle(Text::Bold);
		title.setCharacterSize(180);
		title.setPosition(650.0f, 50.0f);
		title.setFont(font);
		title.setString("Andy's Quest");
		title.setFillColor(Color(20, 30, 70));
		//Title2
		title2.setStyle(Text::Bold);
		title2.setCharacterSize(120);
		title2.setPosition(600.0f, 30.0f);
		title2.setFont(font);
		title2.setString("Andy's Quest");
		title2.setFillColor(Color::White);
		//Play
		play.setStyle(Text::Bold);
		play.setCharacterSize(80);
		play.setPosition(280.0f, 260.0f);
		play.setFont(font);
		play.setString("Play");
		play.setFillColor(Color::White);
		//Instructions
		instruction.setStyle(Text::Bold);
		instruction.setCharacterSize(80);
		instruction.setPosition(215.0f, 410.0f);
		instruction.setFont(font);
		instruction.setString("Instructions");
		instruction.setFillColor(Color::White);
		//Exit
		exit.setStyle(Text::Bold);
		exit.setCharacterSize(80);
		exit.setPosition(290.0f, 560.0f);
		exit.setFont(font);
		exit.setString("Exit");
		exit.setFillColor(Color::White);
		//User Action Effects
		while (window.isOpen())
		{
			while (window.pollEvent(Mouse_Action))
			{
				//Menu Options
				switch (Mouse_Action.type)
				{
				case Event::Closed: //Case 0: Screen is closed
					window.close();
					break;
				case Event::MouseMoved: //Case 1: Mouse is moved into the area of one of the options
				{
					Vector2i mousePos = Mouse::getPosition(window);
					Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					//Play
					if (playBoxImage.getGlobalBounds().contains(mousePosF))
					{
						playBoxImage.setColor(Color(40, 40, 120));
					}
					else
					{
						playBoxImage.setColor(Color(255, 255, 255));
					}
					//Instructions
					if (instructionBoxImage.getGlobalBounds().contains(mousePosF))
					{
						instructionBoxImage.setColor(Color(40, 40, 120));
					}
					else
					{
						instructionBoxImage.setColor(Color(255, 255, 255));
					}
					//Exit
					if (exitBoxImage.getGlobalBounds().contains(mousePosF))
					{
						exitBoxImage.setColor(Color(40, 40, 120));
					}
					else
					{
						exitBoxImage.setColor(Color(255, 255, 255));
					}
				}
				break;
				case Event::MouseButtonPressed: //Case 2: Selecion is made
				{
					Vector2i mousePos = Mouse::getPosition(window);
					Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (playBoxImage.getGlobalBounds().contains(mousePosF))
					{
						cout << "Game Prompted" << endl;
//Play Game
						playBoxImage.setColor(Color(0, 0, 0));
						/*if (!clock_start)
						{
							clock_start = true;
							clock.restart();
						}
						if (clock_start = true)
						{
							if (clock.getElapsedTime().asMilliseconds() == 250)
								playBoxImage.setColor(Color(0, 0, 0));
							if (clock.getElapsedTime().asMilliseconds() == 500)
								playBoxImage.setColor(Color(40, 40, 120));
							if (clock.getElapsedTime().asMilliseconds() == 750)
								playBoxImage.setColor(Color(0, 0, 0));
							if (clock.getElapsedTime().asMilliseconds() == 1000)
								playBoxImage.setColor(Color(40, 40, 120));
						}*/
						return true;


					}
					else if (instructionBoxImage.getGlobalBounds().contains(mousePosF))
					{
						cout << "Instructions Prompted" << endl;
//Instructions
						instructionBoxImage.setColor(Color(0, 0, 0));
						//Rules(Background)
						rulesBox.loadFromFile("Graybox.png");
						rulesBoxImage.setPosition(50.0f, 50.0f);
						rulesBoxImage.setScale(3.0f, 7.4f);
						float rulesBoxWidth = rulesBoxImage.getLocalBounds().width;
						float rulesBoxHeight = rulesBoxImage.getLocalBounds().height;
						rulesBoxImage.setTexture(rulesBox);
						//Title Movement
						title.setPosition(2000.0f, 50.0f);
						title2.setPosition(1050.0f, 30.0f);
						//play Text & Image
						playBoxImage.setPosition(1300.0f, 900.0f);
						play.setPosition(1380.0f, 910.0f);
						//Instruction Text & Image
						instructionBoxImage.setPosition(2000.0f, 30.0f);
						instruction.setPosition(365.0f, 30.0f);
						//Exit Text & Image
						exitBoxImage.setPosition(1600.0f,900.0f);
						exit.setPosition(1690.0f, 910.0f);
						//Line 1
						paragraph.setStyle(Text::Bold);
						paragraph.setCharacterSize(50);
						paragraph.setPosition(145.0f, 120.0f);
						paragraph.setFont(font);
						paragraph.setString("In Andy's Quest you will play as avatar: Travis");
						paragraph.setFillColor(Color::White);
						//Line 2
						paragraph1.setStyle(Text::Bold);
						paragraph1.setCharacterSize(50);
						paragraph1.setPosition(57.0f, 240.0f);
						paragraph1.setFont(font);
						paragraph1.setString("The objective is obtain the key in order to unlock the next room.");
						paragraph1.setFillColor(Color::White);
						//Line 3
						paragraph2.setStyle(Text::Bold);
						paragraph2.setCharacterSize(50);
						paragraph2.setPosition(300.0f, 360.0f);
						paragraph2.setFont(font);
						paragraph2.setString("But watch out for Goblins!");
						paragraph2.setFillColor(Color::White);
						//Link
						link.loadFromFile("link.png"); //link file!!!!
						linkImage.setPosition(430.0f, 170.0f);
						float linkWidth = linkImage.getLocalBounds().width;
						float linkHeight = linkImage.getLocalBounds().height;
						linkImage.setTexture(link);
						linkImage.setScale(3.0f, 3.0f);
						//key
						key.loadFromFile("key.png"); //key file!!!!
						keyImage.setPosition(410.0f, 300.0f);
						float keyWidth = linkImage.getLocalBounds().width;
						float keyHeight = keyImage.getLocalBounds().height;
						keyImage.setTexture(key);
						keyImage.setScale(0.5f, 0.5f);
						//goblin
						goblin.loadFromFile("goblin.png"); //goblin file!!!!
						goblinImage.setPosition(435.0f, 420.0f);
						float goblinWidth = goblinImage.getLocalBounds().width;
						float goblinHeight = goblinImage.getLocalBounds().height;
						goblinImage.setTexture(goblin);
						goblinImage.setScale(2.3f, 2.3f);
					}
					else if (exitBoxImage.getGlobalBounds().contains(mousePosF))
					{
						cout << "Exit Propmted" << endl;
//Exit
						exitBoxImage.setColor(Color(0, 0, 0));
						window.close();
						return false;
					}
				}
				break;
				}
			}

			//Initialization 
			window.clear();
			window.draw(backgroundImage);
			window.draw(playBoxImage);
			window.draw(instructionBoxImage);
			window.draw(exitBoxImage);
			window.draw(rulesBoxImage);
			window.draw(title);
			window.draw(title2);
			window.draw(play);
			window.draw(instruction);
			window.draw(exit);
			window.draw(paragraph);
			window.draw(paragraph1);
			window.draw(paragraph2);
			window.draw(linkImage);
			window.draw(keyImage);
			window.draw(goblinImage);
			window.display();
		}
}