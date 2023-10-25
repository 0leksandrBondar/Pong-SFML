#include "GameResultScreen.h"

#include <SFML/Graphics/Text.hpp>

GameResultScreen::GameResultScreen(sf::RenderWindow* window)
	: _font {new sf::Font}, _frame {new sf::RectangleShape}, _gameWindow {window}
{
	initFrameStyle();
}

GameResultScreen::~GameResultScreen()
{
	delete _frame;
	delete _font;
}

sf::RectangleShape& GameResultScreen::shape() const
{
	return *_frame;
}

void GameResultScreen::initFrameStyle()
{
	const sf::Vector2u windowSize = _gameWindow->getSize();
	const sf::Vector2f frameSize = sf::Vector2f(windowSize.x / 1.5, windowSize.y / 1.5);

	_frame->setSize(frameSize);
	_frame->setOrigin(frameSize.x / 2, frameSize.y / 2);
	_frame->setPosition(windowSize.x / 2, windowSize.y / 2);
	_frame->setFillColor(sf::Color::Black);
	_frame->setOutlineColor(sf::Color::Red);
	_frame->setOutlineThickness(2.0f);
}

void GameResultScreen::initTableInFrame()
{
	_font->loadFromFile("Resource/Fonts/arial.ttf");

	sf::Text header;

	initHeader(header);
	initLabels();

	// --------------- line separator between header and columns --------------------------------------
	sf::RectangleShape line(sf::Vector2f(_frame->getSize().x, 2.0f));
	sf::FloatRect lineRect = line.getLocalBounds();
	line.setFillColor(sf::Color::Red);
	line.setOrigin(lineRect.left + lineRect.width / 2.0f, lineRect.top + lineRect.height / 2.0f);
	line.setPosition(_frame->getPosition().x, header.getPosition().y + lineRect.height + 50);

	_gameWindow->draw(header);
	_gameWindow->draw(line);
}

void GameResultScreen::initHeader(sf::Text& header)
{
	header.setFont(*_font);
	header.setString("Victory");
	header.setCharacterSize(50);
	header.setFillColor(sf::Color::Cyan);
	sf::FloatRect textRect = header.getLocalBounds();
	header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	header.setPosition(_frame->getPosition().x, _frame->getPosition().y - _frame->getSize().y / 2 + 50);
}

void GameResultScreen::initLabels()
{
	sf::Text score;
	score.setFont(*_font);
	score.setString("Score:");
	sf::FloatRect rectOfScore = score.getLocalBounds();
	score.setOrigin(rectOfScore.left + rectOfScore.width / 2.0f, rectOfScore.top + rectOfScore.height / 2.0f);
	score.setPosition(_frame->getPosition().x - _frame->getPosition().x / 2, _frame->getPosition().y - _frame->getPosition().y / 3);
	_gameWindow->draw(score);

	sf::Text durationOfTheMatch;
	durationOfTheMatch.setFont(*_font);
	durationOfTheMatch.setString("Duration of the match: ");
	durationOfTheMatch.setOrigin(rectOfScore.left + rectOfScore.width / 2.0f, rectOfScore.top + rectOfScore.height / 2.0f);
	durationOfTheMatch.setPosition(
		_frame->getPosition().x - _frame->getPosition().x / 2, _frame->getPosition().y - _frame->getPosition().y / 4);
	_gameWindow->draw(durationOfTheMatch);

	sf::Text numberOfBouncedBalls;
	numberOfBouncedBalls.setFont(*_font);
	numberOfBouncedBalls.setString("Number of bounced balls: ");
	numberOfBouncedBalls.setOrigin(rectOfScore.left + rectOfScore.width / 2.0f, rectOfScore.top + rectOfScore.height / 2.0f);
	numberOfBouncedBalls.setPosition(
		_frame->getPosition().x - _frame->getPosition().x / 2, _frame->getPosition().y - _frame->getPosition().y / 6);
	_gameWindow->draw(numberOfBouncedBalls);
}
