#include "pauseMenu.h"
#include "IwGx.h"
#include "input.h"
#include "sound.h"
#include "s3eVibra.h"
#include "game.h"
#include "audio.h"

Sound* g_pSound;

Sound::~Sound()
{
}

void Sound::SoundFunc()
{
	if (changeSound)
	{
		g_pAudio->PlaySound("audio/ice_skating_2.wav");
	}
}

void Sound::StartMusic()
{
	g_pAudio->PlayMusic("audio/in_game.mp3", true);
}

void Sound::StopMusic() 
{
	g_pAudio->StopMusic();
}