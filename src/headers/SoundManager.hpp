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

	SoundManager(const SoundManager &) = delete;
	SoundManager &operator=(const SoundManager &) = delete;

  private:
	SoundManager();
	~SoundManager();

	Mix_Chunk *gunSound;
	Mix_Chunk *hurtSound;
	Mix_Chunk *backgroundSound;
};

#endif // SOUNG_MANAGER_HPP