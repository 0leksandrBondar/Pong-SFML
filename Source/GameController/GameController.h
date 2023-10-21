#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Player;

class GameController
{
public:
	explicit GameController(sf::RenderWindow* window);
	~GameController();

	void handleMoveEvent();

	void drawPlayers() const;
	void drawCenterLine();

private:
	void setDefaultPositions();

private:
	sf::RenderWindow* _gameWindow;
	Player* _player1;
	Player* _player2;
};
