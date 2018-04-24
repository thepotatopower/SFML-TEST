#include <SFML/Graphics.hpp>
#include "Rectangle.h"
using sf::Sprite;

//copy constructor not complete, do not initialize gSprite without intializing its values
class gSprite
{
public:
	gSprite(void);
	gSprite(const gSprite &sprite);
	gSprite(int width, int height, sf::Texture &texture);
	int height;
	int width;
	Sprite sprite;
};

bool hitInd(gSprite sprite1, gSprite sprite2, char direction); //'w' for up, 'a' for left, 's' for down, 'd' for right
bool hitInd(gSprite sprite, Rec rec, char direction);