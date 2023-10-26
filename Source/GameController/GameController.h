#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
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
	void initCenterLine();

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
	sf::Vector2f _ballVelocity {-0.15, 0.15};
	sf::Text* _playerScore;
	sf::Text* _botScore;
	sf::Text* _exitHint;
	sf::Text* _continueHint;
	sf::Font* _font;

	sf::RenderTexture* _lineTexture;
	sf::Sprite* _lineSprite;
	sf::RectangleShape* _lineSegment;

private:
	Player* _bot;
	Player* _player;
	GameResultScreen* _gameResultScreen;

	const float _botVelocity {0.1};
	const float _playerVelocity {0.2};

	const int _spacing = 10;

	bool _isMatchOver {false};
	bool _isRoundFinished {true};
};

