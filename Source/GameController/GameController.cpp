#include "GameController.h"

#include "ResourceManager.h"

#include <SFML/Window/Keyboard.hpp>
#include <random>

GameController::GameController(sf::RenderWindow& window)
	: _ball {sf::CircleShape(10, 10)}, _gameWindow {window}, _gameResultScreen {GameResultScreen(window)}

{
	_ball.setFillColor(sf::Color::Green);
	ResourceManager::instance()->initResources();
	initCenterLine();
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

/*!
 * \brief GameController::handleMoveEvent This method handles the user's button presses to move the platforms.
 */
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
	const sf::Vector2f windowSize = static_cast<sf::Vector2f>(_gameWindow.getSize());
	const auto centerX {windowSize.x / 2};

	_player.shape().setPosition(centerX - (centerX / 2), windowSize.y / 2);
	_bot.shape().setPosition(centerX + (centerX / 2), windowSize.y / 2);
	_ball.setPosition(centerX, _gameWindow.getSize().y / 2);

	ResourceManager::instance()->getLabel(Label::BotScore)->setPosition(centerX + centerX / 5, 15);
	ResourceManager::instance()->getLabel(Label::PlayerScore)->setPosition(centerX - centerX / 2, 15);
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

/*!
 * \brief GameController::updateBallPosition this method handles bouncing the ball off the platforms and calculates new coordinates
 * for the ball then moves it.
 */
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
		ResourceManager::instance()->getSound(Sound::HitSound)->play();
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

/*!
 * \brief GameController::handleBotBehavior this method implements the behavior of the bot and its shuffling relative to the ball
 * positions.
 */
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
	ResourceManager::instance()->updateBotScore(_bot.score());
	ResourceManager::instance()->updatePlayerScore(_player.score());
	_gameWindow.draw(*ResourceManager::instance()->getLabel(Label::BotScore));
	_gameWindow.draw(*ResourceManager::instance()->getLabel(Label::PlayerScore));
}

/*!
 * \brief GameController::checkTheWinner this method handles the completion of the round/game and determines the winner.
 */
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
			_gameResultScreen.setGameResultFields(_player.score(), _bot.score());
			if (_player.score() > 10 || _bot.score() <= 10)
			{
				_gameResultScreen.isPlayerWinner(true);
			}
			_isMatchOver = true;
			const auto elapsedTime = _timer.getElapsedTime();
			_gameResultScreen.setElapsedTime(elapsedTime);
			resetScores();
		}
		resetItemsPosition();
		initFirstDirection();
	}
}

/*!
 * \brief GameController::resetItemsPosition this method sets the positions to the center of the screen for all graphic items.
 */
void GameController::resetItemsPosition()
{
	const sf::Vector2u center {_gameWindow.getSize().x / 2, _gameWindow.getSize().y / 2};

	_ball.setPosition(center.x, center.y);
	_bot.shape().setPosition(center.x + (center.x / 2), _gameWindow.getSize().y / 2);
	_player.shape().setPosition(center.x - (center.x / 2), _gameWindow.getSize().y / 2);
}

/*!
 * \brief  GameController::start this method performs all the game logic of drawing graphical items and processing the game logic.
 */
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
			if (_needRestartTimer)
			{
				_timer.restart();
				_needRestartTimer = false;
			}
		}
	}
	else
	{
		drawGameResult();
	}
}

void GameController::drawGameResult()
{
	_gameResultScreen.drawGameResultScreen();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_isMatchOver = false;
		_needRestartTimer = true;
	}
}

void GameController::drawHints()
{
	_gameWindow.draw(*ResourceManager::instance()->getLabel(Label::ExitHint));
	if (_isRoundFinished)
	{
		_gameWindow.draw(*ResourceManager::instance()->getLabel(Label::ContinueHint));
	}
}

void GameController::initHints()
{
	const sf::Vector2u windowSize = _gameWindow.getSize();

	const sf::FloatRect exitHintRect = ResourceManager::instance()->getLabel(Label::ExitHint)->getLocalBounds();
	ResourceManager::instance()->getLabel(Label::ExitHint)->setPosition(20, windowSize.y - (exitHintRect.height + 20));

	const sf::FloatRect continueHintRect = ResourceManager::instance()->getLabel(Label::ContinueHint)->getLocalBounds();
	ResourceManager::instance()
		->getLabel(Label::ContinueHint)
		->setPosition(windowSize.x / 2 - continueHintRect.width / 2, windowSize.y / 4);
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

/*!
 * \brief GameController::resetScores this method resets the score value after the game is over.
 */
void GameController::resetScores()
{
	_player.resetScore();
	_bot.resetScore();
}
