#include "GameResultScreen.h"

#include "ResourceManager.h"

namespace Constants
{
const std::string playerScoreText {"Player score: "};
const std::string botScoreText {"Bot score : "};
const std::string isWinnerText {"Victory "};
const std::string MatchDurationText {"Duration of the match: "};
}	 // namespace Constants

GameResultScreen::GameResultScreen(sf::RenderWindow& window) : _gameWindow {window}
{
	initLabels();
}

void GameResultScreen::setDefaultPositionForLabels()
{
	const sf::Vector2u windowSize = _gameWindow.getSize();

	for (const auto& label : _labels)
	{
		const sf::FloatRect labelRect = label.second->getLocalBounds();
		switch (label.first)
		{
			case StatisticLabels::PlayerScore:
			{
				label.second->setPosition((windowSize.x - labelRect.width) / 5, (windowSize.y - labelRect.height) / 3);
				break;
			}
			case StatisticLabels::BotScore:
			{
				label.second->setPosition((windowSize.x - labelRect.width) / 5, (windowSize.y - labelRect.height) / 4);
				break;
			}
			case StatisticLabels::isWinner:
			{
				label.second->setPosition((windowSize.x - labelRect.width) / 2, (windowSize.y - labelRect.height) / 7);
				break;
			}
			case StatisticLabels::MatchDuration:
			{
				label.second->setPosition((windowSize.x - labelRect.width) / 4.5, (windowSize.y - labelRect.height) / 2.5);
				break;
			}
		}
	}
}

void GameResultScreen::initLabels()
{
	addLabel(StatisticLabels::isWinner, Constants::isWinnerText);
	addLabel(StatisticLabels::BotScore, Constants::botScoreText);
	addLabel(StatisticLabels::PlayerScore, Constants::playerScoreText);
	addLabel(StatisticLabels::MatchDuration, Constants::MatchDurationText);

	setLabelStyles();
	setDefaultPositionForLabels();
}

void GameResultScreen::drawGameResultScreen()
{
	updateResultData();
	for (const auto& label : _labels)
	{
		_gameWindow.draw(*label.second);
	}
}

void GameResultScreen::setGameResultFields(int playerScore, int botScore)
{
	_playerScore = playerScore;
	_botScore = botScore;
}

void GameResultScreen::setElapsedTime(sf::Time elapsedTime)
{
	_elapsedTime = elapsedTime;
}

void GameResultScreen::isPlayerWinner(bool status)
{
	_isPlayerWinner = status;
}

void GameResultScreen::addLabel(StatisticLabels statisticLabels, const std::string& text)
{
	_labels.emplace(statisticLabels, std::make_shared<sf::Text>(text, *ResourceManager::instance()->getFont(Font::Arial)));
}

void GameResultScreen::setLabelStyles()
{
	for (auto& label : _labels)
	{
		if (label.first == StatisticLabels::isWinner)
		{
			label.second->setCharacterSize(70);
		}
		else
		{
			label.second->setCharacterSize(40);
		}
	}
}

void GameResultScreen::updateResultData()
{
	const std::string victoryLabel {"Victory"};
	const std::string lossLabel {"Loss"};
	const std::string result {_isPlayerWinner ? victoryLabel : lossLabel};
	const sf::Color Color {_isPlayerWinner ? sf::Color::Cyan : sf::Color::Red};

	for (auto& label : _labels)
	{
		switch (label.first)
		{
			case StatisticLabels::PlayerScore:
				label.second->setString(Constants::playerScoreText + std::to_string(_playerScore));
				break;
			case StatisticLabels::BotScore:
				label.second->setString(Constants::botScoreText + std::to_string(_botScore));
				break;
			case StatisticLabels::isWinner:
				label.second->setString(result);
				label.second->setFillColor(Color);
				break;
			case StatisticLabels::MatchDuration:
				label.second->setString(Constants::MatchDurationText + std::to_string(_elapsedTime.asSeconds()) + " sec.");
				break;
		}
	}
}
