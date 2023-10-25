#include "MainWindow.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

MainWindow::MainWindow()
	: _gameWindow(std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Pong", sf::Style::Fullscreen))
	, _gameController {std::make_unique<GameController>(_gameWindow.get())}
{
}

void MainWindow::startGameLoop()
{
	while (_gameWindow->isOpen())
	{
		handleControlBarEvent();

		_gameWindow->clear(sf::Color::Black);
		_gameController->start();
		_gameWindow->display();
	}
}

void MainWindow::handleControlBarEvent()
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
