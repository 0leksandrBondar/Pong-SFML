#pragma once

class Player
{
public:
	Player() = default;

	int score() const;
	void increaseScore();

private:
	unsigned int _score {0};
};