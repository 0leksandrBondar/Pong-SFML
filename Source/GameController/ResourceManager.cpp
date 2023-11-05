#include "ResourceManager.h"

#include <SFML/Audio/SoundBuffer.hpp>
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

void ResourceManager::addFont(Font font, const std::filesystem::path& path)
{
	auto* Font = new sf::Font;
	Font->loadFromFile(path.string());
	_fonts.emplace(font, Font);
}

void ResourceManager::initSoundResources()
{
	addSound(Sound::HitSound, "Resource/Music/Paddle_Hit_Sound.wav");
	addSound(Sound::Background, "Resource/Music/Background_Music.wav");
}

sf::Sound* ResourceManager::getSound(Sound sound) const
{
	const auto it = _sounds.find(sound);
	if (it != _sounds.cend())
	{
		return it->second.second;
	}
	return nullptr;
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

void ResourceManager::addSound(Sound sound, const std::filesystem::path& path)
{
	auto* Sound = new sf::Sound;
	auto* buffer = new sf::SoundBuffer;

	buffer->loadFromFile(path.string());
	Sound->setBuffer(*buffer);

	_sounds.emplace(sound, std::make_pair(buffer, Sound));
}
