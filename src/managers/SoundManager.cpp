#include "SoundManager.hpp"
#include "../utils/SDLException.hpp"
#include "../utils/Utils.hpp"
#include <string>

SoundManager::SoundManager() {

	soundOn = getArg<bool>("sound");

	background = initialize("background.wav");
	background2 = initialize("background2.wav");
	gunShot = initialize("gun_shot.wav");
	gameOver = initialize("game_over.wav");
	collectAmmo = initialize("reload_ammo.wav");
	collectHealth = initialize("collect_health.wav");
	success = initialize("success.wav");
	win = initialize("win.wav");
}

Mix_Chunk *SoundManager::initialize(const std::string &wav) {
	std::string wavPath = getResourcePath("sounds") + wav;
	Mix_Chunk *sound = Mix_LoadWAV(wavPath.c_str());
	if (!sound)
		throw SDLException("Mix_LoadWAV failed for " + wavPath);
	return sound;
}

SoundManager::~SoundManager() {
	Mix_FreeChunk(gunShot);
	Mix_FreeChunk(background);
	Mix_FreeChunk(background);
	Mix_FreeChunk(gameOver);
	Mix_FreeChunk(success);
	Mix_FreeChunk(collectAmmo);
	Mix_FreeChunk(collectHealth);
	Mix_FreeChunk(win);
}

void SoundManager::play(int channel, Mix_Chunk *sound, int times) {
	if (soundOn)
		Mix_PlayChannel(channel, sound, times);
}

void SoundManager::playBackgroundSound() {
	Mix_HaltChannel(0);
	play(0, background, -1);
}

void SoundManager::playBackground2Sound() {
	Mix_HaltChannel(0);
	play(0, background2, -1);
}

void SoundManager::playGunSound() {
	play(1, gunShot, 0);
}

void SoundManager::playGameOverSound() {
	play(1, gameOver, 0);
}

void SoundManager::playCollectHealthSound() {
	play(1, collectHealth, 0);
}

void SoundManager::playReloadGun() {
	play(1, collectAmmo, 0);
}

void SoundManager::playSuccessSound() {
	play(1, success, 0);
}

void SoundManager::playWinSound() {
	play(1, win, 0);
}
