/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#if !defined(__AUDIO_H__)
#define __AUDIO_H__

#include "IwSound.h"
#include <list>

class AudioSound
{
public:
	// Constructor & Destructor
    AudioSound() : m_SoundData(0), m_SoundSpec(0) {}
    ~AudioSound();

	// Member functions
	bool Load(const char* filename);

	// Member variables
    unsigned int    m_NameHash;         // Hashed string name of sound effect
    CIwSoundData*   m_SoundData;        // Sound effect data
    CIwSoundSpec*   m_SoundSpec;        // Sound effect specification
};

class Audio
{
protected:
public:
	// Constructor & Destructor
    Audio();
    ~Audio();

	// Member functions
    AudioSound* findSound(unsigned int name_hash);
	AudioSound* PreloadSound(const char* filename);
    void Update();
	void PlaySound(const char* filename);
    static void PlayMusic(const char* filename, bool repeat = true);
    static void StopMusic();

	// Member variables
	std::list<AudioSound*> m_Sounds;                // List of sound effects
};

extern Audio*   g_pAudio;


#endif  // __AUDIO_H__


