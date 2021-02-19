#ifndef SOUNG_MANAGER_HPP
#define SOUNG_MANAGER_HPP

#include <SDL_mixer.h>
#include <string>

class SoundManager {

  public:
	SoundManager();
	~SoundManager();

	void playBackgroundSound();
	void playBackground2Sound();
	void playGunSound();
	void playGameOverSound();
	void playCollectHealthSound();
	void playReloadGun();
	void playSuccessSound();
	void playWinSound();

  private:
	void play(int channel, Mix_Chunk *sound, int times);
	Mix_Chunk *initialize(const std::string &wav);

	Mix_Chunk *gunShot;
	Mix_Chunk *background;
	Mix_Chunk *background2;
	Mix_Chunk *gameOver;
	Mix_Chunk *collectHealth;
	Mix_Chunk *collectAmmo;
	Mix_Chunk *success;
	Mix_Chunk *win;

	bool soundOn;
};

#endif // SOUNG_MANAGER_HPP