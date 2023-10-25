#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

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

	void drawScoreLabels();
	void start();

private:
	void setDefaultPositions();
	void initFirstDirection();
	void initLabelsStyle();

private:
	sf::CircleShape* _ball;
	sf::RenderWindow* _gameWindow;
	sf::Vector2f _ballVelocity {-0.3, 0.3};
	sf::Text* _playerScore;
	sf::Text* _botScore;
	sf::Font* _font;

private:
	Player* _bot;
	Player* _player;

	const float _botVelocity {0.2};
	const float _playerVelocity {0.3};

	bool _isMathFinished {false};
};
