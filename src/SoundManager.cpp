#include "headers/SoundManager.hpp"
#include "headers/SDLException.hpp"
#include "headers/Utils.hpp"
#include <string>

SoundManager::SoundManager() {
	std::string wav = getResourcePath("sounds") + "gun_shot.wav";
	gunSound = Mix_LoadWAV(wav.c_str());
	if (!gunSound)
		throw SDLException("Mix_LoadWAV failed.");

	wav = getResourcePath("sounds") + "hurt.wav";
	hurtSound = Mix_LoadWAV(wav.c_str());
	if (!hurtSound)
		throw SDLException("Mix_LoadWAV failed.");

	wav = getResourcePath("sounds") + "background.wav";
	backgroundSound = Mix_LoadWAV(wav.c_str());
	if (!backgroundSound)
		throw SDLException("Mix_LoadWAV failed.");
}

SoundManager &SoundManager::getInstance() {
	static SoundManager sm{};
	return sm;
}

void SoundManager::playBackgroundSound() {
	// play endless on channel 0
	Mix_PlayChannel(0, backgroundSound, -1);
}

void SoundManager::playGunSound() {
	Mix_PlayChannel(1, gunSound, 0);
}

void SoundManager::playHurtSound() {
	Mix_PlayChannel(1, hurtSound, 0);
}
