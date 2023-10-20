#include "MainWindow.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

MainWindow::MainWindow() : _mainWindow(std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Pong"))
{
}

void MainWindow::startGameLoop()
{
	while (_mainWindow->isOpen())
	{
		handleControlBarEvent();
	}
}

void MainWindow::handleControlBarEvent()
{
	sf::Event event;
	while (_mainWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_mainWindow->close();
		}
	}
}
