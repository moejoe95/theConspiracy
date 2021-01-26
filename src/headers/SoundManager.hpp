#ifndef SOUNG_MANAGER_HPP
#define SOUNG_MANAGER_HPP

#include "SDL_mixer.h"

/*
this is a Meyers Singleton implementation, see:
https://laristra.github.io/flecsi/src/developer-guide/patterns/meyers_singleton.html
*/
class SoundManager {

  public:
	static SoundManager &getInstance();
	void playBackgroundSound();
	void playGunSound();
	void playHurtSound();
	void playGameOverSound();
	void playCollectHealthSound();
	void playReloadGun();

	SoundManager(const SoundManager &) = delete;
	SoundManager &operator=(const SoundManager &) = delete;

  private:
	SoundManager();
	~SoundManager();
	void play(int channel, Mix_Chunk *sound, int times);

	bool soundOn;
	Mix_Chunk *gunSound;
	Mix_Chunk *hurtSound;
	Mix_Chunk *backgroundSound;
	Mix_Chunk *gameOverSound;
	Mix_Chunk *collect_health;
	Mix_Chunk *collect_ammo;
};

#endif // SOUNG_MANAGER_HPP