#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Player
{
public:
	Player();

	unsigned score() const;
	void increaseScore();

	void updatePos(sf::Vector2f newPos);
	sf::Vector2f getPos();

	sf::RectangleShape& shape();

private:
	unsigned int _score {0};
	sf::RectangleShape _shape;
};