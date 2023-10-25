#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameResultScreen
{
public:
	explicit GameResultScreen(sf::RenderWindow* window = nullptr);
	~GameResultScreen();

	[[nodiscard]] sf::RectangleShape& shape() const;

	void initTableInFrame();

private:
	void initFrameStyle();
	void initHeader(sf::Text& header);
	void initLabels();

private:
	sf::Font* _font;
	sf::RectangleShape* _frame;
	sf::RenderWindow* _gameWindow;
};
