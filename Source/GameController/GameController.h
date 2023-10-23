#pragma once

#include <SFML/Graphics/CircleShape.hpp>
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

	void updateBallPosition();
	void handleBot();

	void start();
private:
	void setDefaultPositions();
	void initFirstDirection();

private:
	sf::CircleShape* _ball;
	sf::RenderWindow* _gameWindow;
	Player* _player1;
	Player* _bot;
	const float _botSpeed {0.175};

	sf::Vector2f _ballVelocity {-0.1, 0.1};
};
