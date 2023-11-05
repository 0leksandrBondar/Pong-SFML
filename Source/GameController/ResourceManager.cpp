#include "ResourceManager.h"

#include <memory>

ResourceManager::ResourceManager()
{
	initFontResources();
	initSoundResources();
	initLabelsResources();
	initLabelStyles();
}

ResourceManager* ResourceManager::instance()
{
	static std::unique_ptr<ResourceManager> _instance;
	if (_instance == nullptr)
	{
		_instance = std::unique_ptr<ResourceManager>(new ResourceManager);
	}
	return _instance.get();
}

void ResourceManager::initFontResources()
{
	addFont(Font::Arial, "Resource/Fonts/arial.ttf");
}

void ResourceManager::addFont(Font font, const std::string& path)
{
	auto* Font = new sf::Font;
	Font->loadFromFile(path);
	_fonts.emplace(font, Font);
}

void ResourceManager::initSoundResources()
{
	_sounds.emplace(Sound::HitSound, "Resource/Music/Paddle_Hit_Sound.wav");
	_sounds.emplace(Sound::Background, "Resource/Music/Background_Music.wav");
}

std::string ResourceManager::getSound(Sound sound) const
{
	const auto it = _sounds.find(sound);
	if (it != _sounds.cend())
	{
		return it->second.string();
	}
	else
	{
		return "";
	}
}

sf::Font* ResourceManager::getFont(Font font) const
{
	const auto it = _fonts.find(font);
	if (it != _fonts.cend())
	{
		return it->second;
	}
	return nullptr;
}

void ResourceManager::initLabelsResources()
{
	addText("Press ESC to close the program", Label::ExitHint);
	addText("Press SPACE to start the game", Label::ContinueHint);
	addText("Player score: ", Label::PlayerScore);
	addText("Bot score: ", Label::BotScore);
}

sf::Text* ResourceManager::getLabel(Label label) const
{
	const auto it = _labels.find(label);
	if (it != _labels.cend())
	{
		return _labels.find(label)->second;
	}
	return nullptr;
}

void ResourceManager::addText(const std::string& text, Label label)
{
	auto* Text = new sf::Text(text, *getFont(Font::Arial));
	_labels.emplace(label, Text);
}

void ResourceManager::initResources()
{
	initLabelsResources();
}

void ResourceManager::initLabelStyles()
{
	auto hint = getLabel(Label::ContinueHint);
	hint->setFillColor(sf::Color::Yellow);

	auto botScoreLabel = getLabel(Label::BotScore);
	botScoreLabel->setStyle(sf::Text::Bold);
	botScoreLabel->setCharacterSize(50);
	botScoreLabel->setFillColor(sf::Color::Green);

	auto playerScoreLabel = getLabel(Label::PlayerScore);
	playerScoreLabel->setStyle(sf::Text::Bold);
	playerScoreLabel->setCharacterSize(50);
	playerScoreLabel->setFillColor(sf::Color::Green);
}

void ResourceManager::updateBotScore(int score)
{
	static std::string text = "Bot score: ";
	static auto botScoreLabel = getLabel(Label::BotScore);
	if (botScoreLabel != nullptr)
	{
		botScoreLabel->setString(text + std::to_string(score));
	}
}

void ResourceManager::updatePlayerScore(int score)
{
	static std::string text = "Player score: ";
	static auto playerScoreLabel = getLabel(Label::PlayerScore);
	if (playerScoreLabel != nullptr)
	{
		playerScoreLabel->setString(text + std::to_string(score));
	}
}
