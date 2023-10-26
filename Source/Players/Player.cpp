#include "Player.h"

Player::Player() : _shape {sf::RectangleShape(sf::Vector2f(30.f, 200.f))}
{
	_shape.setFillColor(sf::Color::Red);
}

void Player::increaseScore()
{
	++_score;
}

unsigned int Player::score() const
{
	return _score;
}

sf::RectangleShape& Player::shape()
{
	return _shape;
}
