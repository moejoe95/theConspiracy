#include "headers/SoundManager.hpp"
#include "headers/SDLException.hpp"
#include "headers/Utils.hpp"
#include <string>

SoundManager::SoundManager() {

	// TODO refactor
	std::string wav = getResourcePath("sounds") + "gun_shot.wav";
	gunSound = Mix_LoadWAV(wav.c_str());
	if (!gunSound)
		throw SDLException("Mix_LoadWAV failed.");

	wav = getResourcePath("sounds") + "background.wav";
	backgroundSound = Mix_LoadWAV(wav.c_str());
	if (!backgroundSound)
		throw SDLException("Mix_LoadWAV failed.");

	wav = getResourcePath("sounds") + "game_over.wav";
	gameOverSound = Mix_LoadWAV(wav.c_str());
	if (!gameOverSound)
		throw SDLException("Mix_LoadWAV failed.");

	wav = getResourcePath("sounds") + "collect_health.wav";
	collect_health = Mix_LoadWAV(wav.c_str());
	if (!collect_health)
		throw SDLException("Mix_LoadWAV failed.");

	wav = getResourcePath("sounds") + "reload_ammo.wav";
	collect_ammo = Mix_LoadWAV(wav.c_str());
	if (!collect_ammo)
		throw SDLException("Mix_LoadWAV failed.");

	soundOn = getArg<bool>("sound");
}

SoundManager::~SoundManager() {
	Mix_FreeChunk(gunSound);
	Mix_FreeChunk(backgroundSound);
	Mix_FreeChunk(gameOverSound);
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

void SoundManager::playGameOverSound() {
	play(1, gameOverSound, 0);
}

void SoundManager::playCollectHealthSound() {
	play(1, collect_health, 0);
}

void SoundManager::playReloadGun() {
	play(1, collect_ammo, 0);
}
