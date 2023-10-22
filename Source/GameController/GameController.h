#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Player;
class Ball;

class GameController
{
public:
	explicit GameController(sf::RenderWindow* window);
	~GameController();

	void handleMoveEvent();

	void drawPlayers() const;
	void drawCenterLine();

	void updateBallPosition();

private:
	void setDefaultPositions();
	void initFirstDirection();

private:
	sf::RenderWindow* _gameWindow;
	Player* _player1;
	Player* _player2;
	Ball* _ball;

	sf::Vector2f _ballVelocity {-0.1, 0.1};
};
