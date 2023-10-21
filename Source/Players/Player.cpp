#include "Player.h"

Player::Player() : _shape {sf::Vector2f(30.f, 200.f)}
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

void Player::updatePos(sf::Vector2f newPos)
{
	_shape.move(newPos);
}

sf::Vector2f Player::getPos()
{
	return _shape.getPosition();
}
