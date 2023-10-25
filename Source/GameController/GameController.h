#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Player;
class GameResultScreen;

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

	void checkTheWinner();
	void resetItemsPosition();

	void start();

private:
	void setDefaultPositions();
	void initFirstDirection();
	void initLabelsStyle();

	void initHints();
	void showHints();
	void showGameResult();

private:
	sf::CircleShape* _ball;
	sf::RenderWindow* _gameWindow;
	sf::Vector2f _ballVelocity {-0.3, 0.3};
	sf::Text* _playerScore;
	sf::Text* _botScore;
	sf::Text* _exitHint;
	sf::Text* _continueHint;
	sf::Font* _font;

private:
	Player* _bot;
	Player* _player;
	GameResultScreen* _gameResultScreen;

	const float _botVelocity {0.2};
	const float _playerVelocity {0.3};

	bool _isMatchOver {false};
	bool _isRoundFinished {true};
};

