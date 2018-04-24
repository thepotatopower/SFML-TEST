#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Rectangle.h"
class master_map : public Rec
{
public:
	master_map(sf::Vector2u window);
	Rec top_barrier;
	Rec bottom_barrier;
	Rec left_barrier;
	Rec right_barrier;
};