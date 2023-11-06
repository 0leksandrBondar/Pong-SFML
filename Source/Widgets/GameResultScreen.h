#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <unordered_map>

enum class StatisticLabels
{
	PlayerScore,
	BotScore,
	isWinner,
	MatchDuration
};

class GameResultScreen
{
public:
	explicit GameResultScreen(sf::RenderWindow& window);

	void drawGameResultScreen();

	void setGameResultFields(int playerScore, int botScore);
	void setElapsedTime(sf::Time elapsedTime);
	void isPlayerWinner(bool status);

private:
	void updateResultData();
	void initLabels();
	void setLabelStyles();
	void setDefaultPositionForLabels();
	void addLabel(StatisticLabels statisticLabels, const std::string& text);

private:
	std::unordered_map<StatisticLabels, std::shared_ptr<sf::Text>> _labels;

	sf::RectangleShape _line;
	sf::RectangleShape _frame;
	sf::RenderWindow& _gameWindow;

private:
	int _playerScore {0};
	int _botScore {0};
	sf::Time _elapsedTime;
	bool _isPlayerWinner {false};
};
