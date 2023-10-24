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
	sf::Vector2f _ballVelocity {-3, 3};

private:
	Player* _bot;
	Player* _player;

	const float _botVelocity {0.8};
	const float _playerVelocity {2};

	bool _isMathFinished {false};
};
