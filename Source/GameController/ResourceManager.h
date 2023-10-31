#pragma once

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

class ResourceManager
{
public:
	static ResourceManager* instance();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	[[nodiscard]] std::string getFont(Font font) const;
	[[nodiscard]] std::string getSound(Sound sound) const;

private:
	ResourceManager();
	void initFontResources();
	void initSoundResources();

private:
	std::unordered_map<Font, std::filesystem::path> _fonts;
	std::unordered_map<Sound, std::filesystem::path> _sounds;
};