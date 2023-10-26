#include "GameResultScreen.h"

GameResultScreen::GameResultScreen(sf::RenderWindow* window) : _gameWindow {*window}
{
	initFrameStyle();
	initTableInFrame();
}

sf::RectangleShape& GameResultScreen::shape()
{
	return _frame;
}

void GameResultScreen::initFrameStyle()
{
	const sf::Vector2u windowSize = _gameWindow.getSize();
	const sf::Vector2f frameSize = sf::Vector2f(windowSize.x / 1.5, windowSize.y / 1.5);

	_frame.setSize(frameSize);
	_frame.setOrigin(frameSize.x / 2, frameSize.y / 2);
	_frame.setPosition(windowSize.x / 2, windowSize.y / 2);
	_frame.setFillColor(sf::Color::Black);
	_frame.setOutlineColor(sf::Color::Red);
	_frame.setOutlineThickness(2.0f);
}

void GameResultScreen::initTableInFrame()
{
	_font.loadFromFile("Resource/Fonts/arial.ttf");

	initHeader();
	initLabels();

	// --------------- _line separator between _header and columns --------------------------------------
	_line.setSize(sf::Vector2f(_frame.getSize().x, 2.0f));
	sf::FloatRect lineRect = _line.getLocalBounds();
	_line.setFillColor(sf::Color::Red);
	_line.setOrigin(lineRect.left + lineRect.width / 2.0f, lineRect.top + lineRect.height / 2.0f);
	_line.setPosition(_frame.getPosition().x, _header.getPosition().y + lineRect.height + 50);
}

void GameResultScreen::initHeader()
{
	_header.setFont(_font);
	_header.setCharacterSize(50);
	sf::FloatRect textRect = _header.getLocalBounds();
	_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_header.setPosition(_frame.getPosition().x, _frame.getPosition().y - _frame.getSize().y / 2 + 50);
}

void GameResultScreen::initLabels()
{
	_score.setFont(_font);
	sf::FloatRect rectOfScore = _score.getLocalBounds();
	_score.setOrigin(rectOfScore.left + rectOfScore.width / 2.0f, rectOfScore.top + rectOfScore.height / 2.0f);
	_score.setPosition(_frame.getPosition().x - _frame.getPosition().x / 2, _frame.getPosition().y - _frame.getPosition().y / 3);

	_durationOfTheMatch.setFont(_font);
	_durationOfTheMatch.setOrigin(rectOfScore.left + rectOfScore.width / 2.0f, rectOfScore.top + rectOfScore.height / 2.0f);
	_durationOfTheMatch.setPosition(
		_frame.getPosition().x - _frame.getPosition().x / 2, _frame.getPosition().y - _frame.getPosition().y / 5);

	_numberOfBouncedBalls.setFont(_font);
	_numberOfBouncedBalls.setOrigin(rectOfScore.left + rectOfScore.width / 2.0f, rectOfScore.top + rectOfScore.height / 2.0f);
	_numberOfBouncedBalls.setPosition(
		_frame.getPosition().x - _frame.getPosition().x / 2, _frame.getPosition().y - _frame.getPosition().y / 8);
}

void GameResultScreen::drawGameResultScreen()
{
	const std::string victoryLabel {"Victory"};
	const std::string lossLabel {"Loss"};
	const auto lable {_isPlayerWinner ? victoryLabel : lossLabel};
	const auto Color {_isPlayerWinner ? sf::Color::Cyan : sf::Color::Red};

	_header.setFillColor(Color);
	_header.setString(lable);

	_durationOfTheMatch.setString("Duration of the match: " + std::to_string(_elapsedTime.asSeconds()) + " sec.");
	_numberOfBouncedBalls.setString("Number of bounced balls: ");
	_score.setString("Player score: " + std::to_string(_playerScore) + "\n Bot score : " + std::to_string(_botScore));

	_gameWindow.draw(_frame);
	_gameWindow.draw(_line);
	_gameWindow.draw(_score);
	_gameWindow.draw(_header);
	_gameWindow.draw(_durationOfTheMatch);
	_gameWindow.draw(_numberOfBouncedBalls);
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
