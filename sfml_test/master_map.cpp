#pragma once
#include "master_map.h"

master_map::master_map(sf::Vector2u window)
{
	this->top_barrier = Rec(*(new sf::Vector2f(window.x*.001, window.y*.001)),
		sf::Color::Green,
		*(new sf::Vector2f(window.x*.99, window.y*0.04)));

	this->bottom_barrier = Rec(*(new sf::Vector2f(window.x*.001, window.y*.96)),
		sf::Color::Green,
		*(new sf::Vector2f(window.x*.99, window.y*0.04)));

	this->left_barrier = Rec(*(new sf::Vector2f(window.x*.96, window.y*.001)),
		sf::Color::Green,
		*(new sf::Vector2f(window.x*.04, window.y*0.99)));

	this->right_barrier = Rec(*(new sf::Vector2f(window.x*.001, window.y*.001)),
		sf::Color::Green,
		*(new sf::Vector2f(window.x*.04, window.y*0.99)));
}

