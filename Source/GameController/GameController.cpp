#include "GameController.h"

#include "Ball.h"
#include "Player.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

GameController::GameController(sf::RenderWindow* window)
	: _gameWindow {window}, _player1 {new Player}, _player2 {new Player}, _ball {new Ball}
{
	setDefaultPositions();
}

GameController::~GameController()
{
	delete _player1;
	delete _player2;
	delete _ball;
}

void GameController::drawPlayers() const
{
	_gameWindow->draw(_player1->shape());
	_gameWindow->draw(_player2->shape());
	_gameWindow->draw(_ball->shape());
}

void GameController::handleMoveEvent()
{
	const float playerSpeed = 0.40;
	const float windowHeight = static_cast<float>(_gameWindow->getSize().y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (_player1->getPos().y + _player1->shape().getSize().y + playerSpeed < windowHeight)
		{
			_player1->updatePos({0, playerSpeed});
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (_player1->getPos().y - playerSpeed > 0)
		{
			_player1->updatePos({0, -playerSpeed});
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (_player2->getPos().y - playerSpeed > 0)
		{
			_player2->updatePos({0, -playerSpeed});
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (_player2->getPos().y + _player1->shape().getSize().y + playerSpeed < windowHeight)
		{
			_player2->updatePos({0, playerSpeed});
		}
	}
}

void GameController::setDefaultPositions()
{
	const sf::Vector2u windowSize = _gameWindow->getSize();
	const auto centerX {windowSize.x / 2};

	_player1->shape().setPosition(centerX - (centerX / 2), windowSize.y / 2);
	_player2->shape().setPosition(centerX + (centerX / 2), windowSize.y / 2);
	_ball->shape().setPosition(_gameWindow->getSize().x / 2, _gameWindow->getSize().y / 2);
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
