#pragma once

#include "GameController.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class MainWindow
{
public:
	MainWindow();

	void startGameLoop();

private:
	void handleControlBarEvent();

	sf::Music _playerMusic;

private:
	std::unique_ptr<sf::RenderWindow> _gameWindow;
	std::unique_ptr<GameController> _gameController;
};
