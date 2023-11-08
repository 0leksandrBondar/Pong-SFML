#pragma once

#include "GameResultScreen.h"
#include "Player.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class GameController
{
public:
	explicit GameController(sf::RenderWindow& window);

	void start();

private:
	void checkTheWinner();
	void handleMoveEvent();
	void handleBotBehavior();
	void updateBallPosition();
	void resetItemsPosition();
	void resetScores();

private:
	void drawHints();
	void drawPlayers();
	void drawGameResult();
	void drawCenterLine();
	void drawScoreLabels();

private:
	void initHints();
	void initCenterLine();
	void initFirstDirection();
	void initDefaultPositions();

private:
	sf::Clock _timer;

	sf::Sprite _lineSprite;
	sf::CircleShape _ball;
	sf::RenderWindow& _gameWindow;
	sf::RenderTexture _lineTexture;
	sf::RectangleShape _lineSegment;

	sf::Vector2f _ballVelocity {-0.15, 0.15};

private:
	Player _bot;
	Player _player;
	GameResultScreen _gameResultScreen;

	const int _spacing = 10;

	const float _botVelocity {0.1};
	const float _playerVelocity {0.2};

	bool _isMatchOver {false};
	bool _isRoundFinished {true};
	bool _needRestartTimer {true};
};
