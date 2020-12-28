#ifndef SOUNG_MANAGER_HPP
#define SOUNG_MANAGER_HPP

#include "SDL_mixer.h"

// Meyers Singleton
class SoundManager {

  public:
	static SoundManager &getInstance();
	void playBackgroundSound();
	void playGunSound();
	void playHurtSound();

  private:
	SoundManager();

	Mix_Chunk *gunSound;
	Mix_Chunk *hurtSound;
	Mix_Chunk *backgroundSound;
};

#endif // SOUNG_MANAGER_HPP