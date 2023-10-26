#include "GameController.h"

#include <SFML/Window/Keyboard.hpp>
#include <random>

GameController::GameController(sf::RenderWindow* window)
	: _ball {sf::CircleShape(10, 10)}, _gameWindow {*window}, _gameResultScreen {GameResultScreen(window)}

{
	_ball.setFillColor(sf::Color::Green);

	initSoundBuffer();
	initCenterLine();
	initLabelsStyle();
	initHints();
	initFirstDirection();
	initDefaultPositions();
}

void GameController::drawPlayers()
{
	_gameWindow.draw(_player.shape());
	_gameWindow.draw(_bot.shape());
	_gameWindow.draw(_ball);
}

void GameController::handleMoveEvent()
{
	const float windowHeight = static_cast<float>(_gameWindow.getSize().y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (_player.shape().getPosition().y + _player.shape().getSize().y + _playerVelocity < windowHeight)
		{
			_player.shape().move({0, _playerVelocity});
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (_player.shape().getPosition().y - _playerVelocity > 0)
		{
			_player.shape().move({0, -_playerVelocity});
		}
	}
}

void GameController::initDefaultPositions()
{
	const sf::Vector2u windowSize = _gameWindow.getSize();
	const auto centerX {windowSize.x / 2};

	_player.shape().setPosition(centerX - (centerX / 2), windowSize.y / 2);
	_bot.shape().setPosition(centerX + (centerX / 2), windowSize.y / 2);
	_ball.setPosition(centerX, _gameWindow.getSize().y / 2);

	_botScore.setPosition(centerX + centerX / 5, 15);
	_playerScore.setPosition(centerX - centerX / 2, 15);
}

void GameController::drawCenterLine()
{
	for (int y = 0; y < _lineTexture.getSize().y; y += (_lineSegment.getSize().y + _spacing))
	{
		_lineSegment.setPosition(0, y);
		_lineTexture.draw(_lineSegment);
	}

	_lineTexture.display();
	_gameWindow.draw(_lineSprite);
}

void GameController::updateBallPosition()
{
	const sf::FloatRect ballBounds = _ball.getGlobalBounds();
	const sf::FloatRect playerBounds = _player.shape().getGlobalBounds();
	const float ballCenterY = ballBounds.top + ballBounds.height / 2;
	const float playerBottom = playerBounds.top + playerBounds.height;

	if (!_isRoundFinished)
	{
		_ball.move(_ballVelocity);
	}

	if (_ball.getPosition().y < 0 || _ball.getPosition().y + _ball.getGlobalBounds().height > _gameWindow.getSize().y)
	{
		_ballVelocity.y = -_ballVelocity.y;
	}

	if (_ball.getGlobalBounds().intersects(_player.shape().getGlobalBounds()) ||
		_ball.getGlobalBounds().intersects(_bot.shape().getGlobalBounds()))
	{
		_sound.play();
		_ballVelocity.x = -_ballVelocity.x;
		if (ballCenterY < playerBounds.top + playerBounds.height / 3)
		{
			_ballVelocity.y -= 0.05f;
		}
		else if (ballCenterY > playerBottom - playerBounds.height / 3)
		{
			_ballVelocity.y += 0.05f;
		}
	}
}

void GameController::initFirstDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> disVertical(-0.3, 0.3);
	_ballVelocity.y = disVertical(gen) * 0.3;
}

void GameController::handleBotBehavior()
{
	const sf::Vector2f ballPosition = _ball.getPosition();
	const sf::Vector2u screenSize = _gameWindow.getSize();
	const sf::Vector2f botPosition = _bot.shape().getPosition();

	if (ballPosition.y < botPosition.y && botPosition.y > 0)
	{
		_bot.shape().move(0.0f, -_botVelocity);
	}
	else if (ballPosition.y > botPosition.y && botPosition.y + _bot.shape().getGlobalBounds().height < screenSize.y)
	{
		_bot.shape().move(0.0f, _botVelocity);
	}
}

void GameController::drawScoreLabels()
{
	_botScore.setString("Bot score: " + std::to_string(_bot.score()));
	_playerScore.setString("Player score: " + std::to_string(_player.score()));
	_gameWindow.draw(_botScore);
	_gameWindow.draw(_playerScore);
}

void GameController::checkTheWinner()
{
	const bool botVictory {_ball.getPosition().x < _player.shape().getPosition().x};
	const bool playerVictory {_ball.getPosition().x > _bot.shape().getPosition().x};

	if (botVictory || playerVictory)
	{
		if (botVictory)
		{
			_bot.increaseScore();
			_isRoundFinished = true;
		}
		else if (playerVictory)
		{
			_player.increaseScore();
			_isRoundFinished = true;
		}

		if (_player.score() > 10 || _bot.score() > 10)
		{
			_isMatchOver = true;
		}
		resetItemsPosition();
		initFirstDirection();
	}
}

void GameController::resetItemsPosition()
{
	const sf::Vector2u center {_gameWindow.getSize().x / 2, _gameWindow.getSize().y / 2};

	_ball.setPosition(center.x, center.y);
	_bot.shape().setPosition(center.x + (center.x / 2), _gameWindow.getSize().y / 2);
	_player.shape().setPosition(center.x - (center.x / 2), _gameWindow.getSize().y / 2);
}

void GameController::start()
{
	if (!_isMatchOver)
	{
		drawCenterLine();
		drawPlayers();
		drawScoreLabels();
		updateBallPosition();
		handleBotBehavior();
		handleMoveEvent();
		checkTheWinner();
		drawHints();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			_isRoundFinished = false;
		}
	}
	else
	{
		drawGameResult();
	}
}

void GameController::initLabelsStyle()
{
	_playerScore.setFont(_font);
	_playerScore.setStyle(sf::Text::Bold);
	_playerScore.setCharacterSize(50);
	_playerScore.setFillColor(sf::Color::Green);

	_botScore.setFont(_font);
	_botScore.setStyle(sf::Text::Bold);
	_botScore.setCharacterSize(50);
	_botScore.setFillColor(sf::Color::Green);
}

void GameController::drawGameResult()
{
	_gameResultScreen.drawGameResultScreen();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_isMatchOver = false;
	}
}

void GameController::drawHints()
{
	_gameWindow.draw(_exitHint);
	if (_isRoundFinished)
	{
		_gameWindow.draw(_continueHint);
	}
}

void GameController::initHints()
{
	_font.loadFromFile("Resource/Fonts/arial.ttf");

	const sf::Vector2u windowSize = _gameWindow.getSize();

	_exitHint.setFont(_font);
	_exitHint.setFillColor(sf::Color::White);
	_exitHint.setString("Press ESC to close the program");
	const sf::FloatRect exitHintRect = _exitHint.getLocalBounds();
	_exitHint.setPosition(20, windowSize.y - (exitHintRect.height + 20));

	_continueHint.setFont(_font);
	_continueHint.setFillColor(sf::Color::White);
	_continueHint.setString("Press SPACE to start the game");
	_continueHint.setFillColor(sf::Color::Yellow);
	const sf::FloatRect continueHintRect = _continueHint.getLocalBounds();
	_continueHint.setPosition(windowSize.x / 2 - continueHintRect.width / 2, windowSize.y / 4);
}

void GameController::initCenterLine()
{
	if (_lineTexture.create(15, _gameWindow.getSize().y))
	{
		_lineTexture.clear(sf::Color::Transparent);
		_lineSegment.setSize(sf::Vector2f(2, 30));
		_lineSegment.setFillColor(sf::Color::White);
		_lineSprite.setTexture(_lineTexture.getTexture());
		_lineSprite.setPosition((_gameWindow.getSize().x - 15) / 2, 0);
	}
}

void GameController::initSoundBuffer()
{
	_soundBuffer.loadFromFile("Resource/Music/Paddle_Hit_Sound.wav");
	_sound.setBuffer(_soundBuffer);
}
