#pragma once

#include <SFML/Graphics/CircleShape.hpp>

class Ball
{
public:
	Ball();
	sf::CircleShape& shape();

private:
	sf::CircleShape _ball;
};