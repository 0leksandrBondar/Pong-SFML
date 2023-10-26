#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Player
{
public:
	Player();

	[[nodiscard]] unsigned int score() const;
	void increaseScore();
	void resetScore();

	sf::RectangleShape& shape();

private:
	unsigned int _score {0};
	sf::RectangleShape _shape;
};