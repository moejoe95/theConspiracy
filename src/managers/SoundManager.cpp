#include "SoundManager.hpp"
#include "../utils/SDLException.hpp"
#include "../utils/Utils.hpp"
#include <spdlog/spdlog.h>
#include <string>

SoundManager::SoundManager() {

	// init soud
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw SDLException("Mix_OpenAudio failed.");

	soundOn = getArg<bool>("sound");

	background = initialize("background.wav");
	background2 = initialize("background2.wav");
	gunShot = initialize("gun_shot.wav");
	gameOver = initialize("game_over.wav");
	collectAmmo = initialize("reload_ammo.wav");
	collectHealth = initialize("collect_health.wav");
	success = initialize("success.wav");
	win = initialize("win.wav");

	Mix_Volume(1, 25);
	Mix_Volume(0, 100);

	spdlog::info("sound manager initialized");
}

Mix_Chunk *SoundManager::initialize(const std::string &wav) {
	std::string wavPath = getResourcePath("sounds") + wav;
	Mix_Chunk *sound = Mix_LoadWAV(wavPath.c_str());
	if (!sound)
		throw SDLException("Mix_LoadWAV failed for " + wavPath);
	return sound;
}

SoundManager::~SoundManager() {
	Mix_FreeChunk(win);
	Mix_FreeChunk(success);
	Mix_FreeChunk(collectHealth);
	Mix_FreeChunk(collectAmmo);
	Mix_FreeChunk(gameOver);
	Mix_FreeChunk(gunShot);
	Mix_FreeChunk(background2);
	Mix_FreeChunk(background);
	Mix_CloseAudio();
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
