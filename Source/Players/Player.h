#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Player
{
public:
	Player();
	virtual ~Player();

	[[nodiscard]] unsigned int score() const;
	void increaseScore();
	void resetScore();

	sf::RectangleShape& shape();

private:
	sf::RectangleShape _shape;
};