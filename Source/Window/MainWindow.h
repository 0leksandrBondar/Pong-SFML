#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class MainWindow
{
public:
	MainWindow();

	void startGameLoop();

private:
	void handleControlBarEvent();

private:
	std::unique_ptr<sf::RenderWindow> _mainWindow;
};
