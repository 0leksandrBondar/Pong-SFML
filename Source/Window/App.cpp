#include "App.h"

#include "ResourceManager.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

App::App()
	: _gameWindow(std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Pong", sf::Style::Fullscreen))
	, _gameController {std::make_unique<GameController>(*_gameWindow)}
{
	_playerMusic.openFromFile(ResourceManager::instance()->getSound(Sound::Background));
}

void App::startGameLoop()
{
	_playerMusic.setLoop(true);
	_playerMusic.play();
	while (_gameWindow->isOpen())
	{
		handleControlBarEvent();

		_gameWindow->clear(sf::Color::Black);
		_gameController->start();
		_gameWindow->display();
	}
}

void App::handleControlBarEvent()
{
	sf::Event event {};

	while (_gameWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			_gameWindow->close();
		}
	}
}
