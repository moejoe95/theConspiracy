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

	soundOn = getArg<bool>("sound");
}

SoundManager::~SoundManager() {
	Mix_FreeChunk(gunSound);
	Mix_FreeChunk(hurtSound);
	Mix_FreeChunk(backgroundSound);
}

SoundManager &SoundManager::getInstance() {
	static SoundManager sm{};
	return sm;
}

void SoundManager::play(int channel, Mix_Chunk *sound, int times) {
	if (soundOn)
		Mix_PlayChannel(channel, sound, times);
}

void SoundManager::playBackgroundSound() {
	// play endless on channel 0
	play(0, backgroundSound, -1);
}

void SoundManager::playGunSound() {
	play(1, gunSound, 0);
}

void SoundManager::playHurtSound() {
	play(1, hurtSound, 0);
}
