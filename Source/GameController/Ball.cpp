#include "Ball.h"

Ball::Ball() : _ball(10, 10)
{
	_ball.setFillColor(sf::Color::Green);
}

sf::CircleShape& Ball::shape()
{
	return _ball;
}
