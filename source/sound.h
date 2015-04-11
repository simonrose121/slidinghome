#if !defined(__SOUND_H__)
#define __SOUND_H__

#include "scene.h"

/*
	Sound class to handle all music and sound
	effects in game
*/
class Sound
{
public:
	// Constructor & Destructor
	Sound() {};
	~Sound();

	// Member functions
	void SoundFunc();
	void StartMusic();
	void StopMusic();

	bool getSound() { return changeSound; }
	void setSoundMode(bool soundOn){ changeSound = soundOn; }
	bool getMusic() { return changeMusic; }
	void setMusicMode(bool musicOn){ changeMusic = musicOn; }
private:
	// Member variables
	bool changeSound;
	bool changeMusic;
};

extern Sound* g_pSound;

#endif  // __SOUND_H__