#include "Player.h"
#include "GameState.h"

Player::Player() : _shape {sf::RectangleShape(sf::Vector2f(30.f, 200.f))}
{
	_shape.setFillColor(sf::Color::Red);
	GetGameState().registerPlayer(*this);
}

Player::~Player()
{
	GetGameState().unregisterPlayer(*this);
}

void Player::increaseScore()
{
	++GetGameState().getPlayerStatistics(*this)->score;
}

unsigned int Player::score() const
{
	return GetGameState().getPlayerStatistics(*this)->score;
}

sf::RectangleShape& Player::shape()
{
	return _shape;
}

void Player::resetScore()
{
	GetGameState().getPlayerStatistics(*this)->score = {};
}
