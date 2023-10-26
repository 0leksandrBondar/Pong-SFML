#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class GameResultScreen
{
public:
	explicit GameResultScreen(sf::RenderWindow* window = nullptr);

	sf::RectangleShape& shape();
	void drawGameResultScreen();

private:
	void initLabels();
	void initHeader();
	void initFrameStyle();
	void initTableInFrame();

private:
	sf::Font _font;
	sf::Text _score;
	sf::Text _header;
	sf::Text _durationOfTheMatch;
	sf::Text _numberOfBouncedBalls;

	sf::RectangleShape _line;
	sf::RectangleShape _frame;
	sf::RenderWindow& _gameWindow;
};
