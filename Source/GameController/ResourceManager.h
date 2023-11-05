#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <filesystem>
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

	[[nodiscard]] sf::Font* getFont(Font font) const;
	[[nodiscard]] std::string getSound(Sound sound) const;
	[[nodiscard]] sf::Text* getLabel(Label label) const;

private:
	ResourceManager();
	void initFontResources();
	void initSoundResources();
	void initLabelsResources();
	void initLabelStyles();

	void addText(const std::string& text, Label label);
	void addFont(Font font, const std::string& path);

private:
	sf::Font _font;
	std::unordered_map<Font, sf::Font*> _fonts;
	std::unordered_map<Label, sf::Text*> _labels;
	std::unordered_map<Sound, std::filesystem::path> _sounds;
};