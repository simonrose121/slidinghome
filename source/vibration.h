#if !defined(__VIBRATION_H__)
#define __VIBRATION_H__

#include "scene.h"

class Vibration
{
public:
	// Constructor & Destructor
	Vibration(int vibrateIntensity, int vibrateTime) : intensity(vibrateIntensity), time(vibrateTime) {}
	~Vibration();

	// Member functions
	void Vibrate();

private:
	// Member variables
	bool vibrationEnabled;
	int time;
	int intensity;
};

extern Vibration* g_pVibration;

#endif  // __VIBRATION_H__