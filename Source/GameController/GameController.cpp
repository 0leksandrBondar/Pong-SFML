#include "GameController.h"

#include "Player.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <random>

GameController::GameController(sf::RenderWindow* window)
	: _ball {new sf::CircleShape(10, 10)}
	, _gameWindow {window}
	, _bot {new Player}
	, _player {new Player}
	, _playerScore {new sf::Text}
	, _botScore {new sf::Text}
	, _font {new sf::Font}

{
	_ball->setFillColor(sf::Color::Green);

	initLabelsStyle();
	initFirstDirection();
	setDefaultPositions();
}

GameController::~GameController()
{
	delete _player;
	delete _bot;
	delete _ball;
	delete _playerScore;
	delete _botScore;
	delete _font;
}

void GameController::drawPlayers() const
{
	_gameWindow->draw(_player->shape());
	_gameWindow->draw(_bot->shape());
	_gameWindow->draw(*_ball);
}

void GameController::handleMoveEvent()
{
	const float windowHeight = static_cast<float>(_gameWindow->getSize().y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (_player->shape().getPosition().y + _player->shape().getSize().y + _playerVelocity < windowHeight)
		{
			_player->shape().move({0, _playerVelocity});
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (_player->shape().getPosition().y - _playerVelocity > 0)
		{
			_player->shape().move({0, -_playerVelocity});
		}
	}
}

void GameController::setDefaultPositions()
{
	const sf::Vector2u windowSize = _gameWindow->getSize();
	const auto centerX {windowSize.x / 2};

	_player->shape().setPosition(centerX - (centerX / 2), windowSize.y / 2);
	_bot->shape().setPosition(centerX + (centerX / 2), windowSize.y / 2);
	_ball->setPosition(centerX, _gameWindow->getSize().y / 2);

	_botScore->setPosition(centerX + 10, 15);
}

void GameController::drawCenterLine()
{
	sf::RenderTexture lineTexture;
	if (lineTexture.create(15, _gameWindow->getSize().y))
	{
		lineTexture.clear(sf::Color::Transparent);

		sf::RectangleShape lineSegment(sf::Vector2f(2, 30));
		lineSegment.setFillColor(sf::Color::White);

		const int spacing = 10;

		for (int y = 0; y < lineTexture.getSize().y; y += (lineSegment.getSize().y + spacing))
		{
			lineSegment.setPosition(0, y);
			lineTexture.draw(lineSegment);
		}

		lineTexture.display();

		sf::Sprite lineSprite(lineTexture.getTexture());
		lineSprite.setPosition((_gameWindow->getSize().x - 15) / 2, 0);

		_gameWindow->draw(lineSprite);
	}
}

void GameController::updateBallPosition()
{
	const sf::FloatRect ballBounds = _ball->getGlobalBounds();
	const sf::FloatRect playerBounds = _player->shape().getGlobalBounds();
	const float ballCenterY = ballBounds.top + ballBounds.height / 2;
	const float playerBottom = playerBounds.top + playerBounds.height;

	_ball->move(_ballVelocity);

	if (_ball->getPosition().y < 0 || _ball->getPosition().y + _ball->getGlobalBounds().height > _gameWindow->getSize().y)
	{
		_ballVelocity.y = -_ballVelocity.y;
	}

	if (_ball->getGlobalBounds().intersects(_player->shape().getGlobalBounds()) ||
		_ball->getGlobalBounds().intersects(_bot->shape().getGlobalBounds()))
	{
		_ballVelocity.x = -_ballVelocity.x;
		if (ballCenterY < playerBounds.top + playerBounds.height / 3)
		{
			_ballVelocity.y -= 0.15f;
		}
		else if (ballCenterY > playerBottom - playerBounds.height / 3)
		{
			_ballVelocity.y += 0.15f;
		}
	}
}

void GameController::initFirstDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 1);

	int randomDirection = dis(gen);

	if (randomDirection == 0)
	{
		_ballVelocity.x = -0.1f;
	}
	else
	{
		_ballVelocity.x = 0.1f;
	}
	std::uniform_int_distribution<int> disVertical(-1, 1);
	_ballVelocity.y = disVertical(gen) * 0.1f;
}

void GameController::handleBot()
{
	sf::Vector2f ballPosition = _ball->getPosition();
	sf::Vector2f botPosition = _bot->shape().getPosition();
	const sf::Vector2u screenSize = _gameWindow->getSize();

	if (ballPosition.y < botPosition.y && botPosition.y > 0)
	{
		_bot->shape().move(0.0f, -_botVelocity);
	}
	else if (ballPosition.y > botPosition.y && botPosition.y + _bot->shape().getGlobalBounds().height < screenSize.y)
	{
		_bot->shape().move(0.0f, _botVelocity);
	}
}

void GameController::drawScoreLabels()
{
	_playerScore->setString("Player score: " + std::to_string(_player->score()));
	const sf::Vector2f playerScorePos {(_gameWindow->getSize().x / 2) - (_playerScore->getLocalBounds().width + 30), 10.0};
	_playerScore->setPosition(playerScorePos);
	_botScore->setString("Bot score: " + std::to_string(_bot->score()));
	_gameWindow->draw(*_playerScore);
	_gameWindow->draw(*_botScore);
}

	{
		_bot->shape().move(0.0f, _botSpeed);
	}
}
void GameController::start()
{
	drawCenterLine();
	drawPlayers();
	drawScoreLabels();
	updateBallPosition();
	handleBot();
	handleMoveEvent();
}

void GameController::initLabelsStyle()
{
	_font->loadFromFile("C:/Users/aleks/Desktop/Pong/Resource/Fonts/arial.ttf");

	_playerScore->setFont(*_font);
	_playerScore->setStyle(sf::Text::Bold);

	_botScore->setFont(*_font);
	_botScore->setStyle(sf::Text::Bold);
}
