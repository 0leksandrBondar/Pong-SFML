#include "ResourceManager.h"

#include <memory>

ResourceManager::ResourceManager()
{
	initFontResources();
	initSoundResources();
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
	_fonts.emplace(Font::Arial, "Resource/Fonts/arial.ttf");
}

void ResourceManager::initSoundResources()
{
	_sounds.emplace(Sound::HitSound, "Resource/Music/Paddle_Hit_Sound.wav");
	_sounds.emplace(Sound::Background, "Resource/Music/Background_Music.wav");
}

std::string ResourceManager::getFont(Font font) const
{
	return _fonts.find(font)->second.string();
}

std::string ResourceManager::getSound(Sound sound) const
{
	return _sounds.find(sound)->second.string();
}
