#include "pauseMenu.h"
#include "IwGx.h"
#include "input.h"
#include "vibration.h"
#include "s3eVibra.h"
#include "game.h"

Vibration* g_pVibration;

Vibration::~Vibration()
{
}

void Vibration::Vibrate()
{
	// vibrate if option is set
	if (changeVibration)
	{
		s3eVibraVibrate(intensity, time);
	}
}