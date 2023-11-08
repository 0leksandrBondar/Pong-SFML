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
	std::shared_ptr<sf::Font> Font = std::make_shared<sf::Font>();
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

std::shared_ptr<sf::Font> ResourceManager::getFont(Font font) const
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

std::shared_ptr<sf::Text> ResourceManager::getLabel(Label label) const
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
	_labels.emplace(label, std::make_shared<sf::Text>(text, *getFont(Font::Arial)));
}

void ResourceManager::initResources()
{
	initLabelsResources();
}

void ResourceManager::initLabelStyles()
{
	for (auto& label : _labels)
	{
		label.second->setStyle(sf::Text::Bold);
		label.second->setCharacterSize(50);
		if (label.first == Label::PlayerScore || label.first == Label::BotScore)
		{
			label.second->setFillColor(sf::Color::Green);
		}
		else if (label.first == Label::ExitHint)
		{
			continue;
		}
		else if (label.first == Label::ContinueHint)
		{
			label.second->setFillColor(sf::Color::Yellow);
		}
	}
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
