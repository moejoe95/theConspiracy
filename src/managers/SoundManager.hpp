#ifndef SOUNG_MANAGER_HPP
#define SOUNG_MANAGER_HPP

#include "SDL_mixer.h"

class SoundManager {

  public:
	SoundManager();
	~SoundManager();
	void playBackgroundSound();
	void playGunSound();
	void playGameOverSound();
	void playCollectHealthSound();
	void playReloadGun();
	void playSuccessSound();

  private:
	void play(int channel, Mix_Chunk *sound, int times);

	bool soundOn;
	Mix_Chunk *gunSound;
	Mix_Chunk *backgroundSound;
	Mix_Chunk *gameOverSound;
	Mix_Chunk *collect_health;
	Mix_Chunk *collect_ammo;
	Mix_Chunk *success;
};

#endif // SOUNG_MANAGER_HPP