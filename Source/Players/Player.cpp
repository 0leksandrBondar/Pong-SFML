#include "Player.h"

void Player::increaseScore()
{
	++_score;
}

int Player::score() const
{
	return _score;
}
