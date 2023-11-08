#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <filesystem>
#include <memory>
#include <unordered_map>

enum class Sound
{
	Background,
	HitSound
};

enum class Font
{
	Arial
};

enum class Label
{
	BotScore,
	PlayerScore,
	ExitHint,
	ContinueHint,

};

class ResourceManager
{
public:
	static ResourceManager* instance();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	void initResources();
	void updateBotScore(int score);
	void updatePlayerScore(int score);

	[[nodiscard]] std::shared_ptr<sf::Font> getFont(Font font) const;
	[[nodiscard]] sf::Sound* getSound(Sound sound) const;
	[[nodiscard]] std::shared_ptr<sf::Text> getLabel(Label label) const;

private:
	ResourceManager();
	void initFontResources();
	void initSoundResources();
	void initLabelsResources();
	void initLabelStyles();

	void addText(const std::string& text, Label label);
	void addFont(Font font, const std::filesystem::path& path);
	void addSound(Sound sound, const std::filesystem::path& path);

private:
	sf::Font _font;
	std::unordered_map<Font, std::shared_ptr<sf::Font>> _fonts;
	std::unordered_map<Label, std::shared_ptr<sf::Text>> _labels;
	std::unordered_map<Sound, std::pair<sf::SoundBuffer*, sf::Sound*>> _sounds;
};