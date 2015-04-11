#if !defined(__VIBRATION_H__)
#define __VIBRATION_H__

#include "scene.h"

/*
	Vibration class to manage vibration
*/
class Vibration
{
public:
	// Constructor & Destructor
	Vibration(int vibrateIntensity, int vibrateTime) : intensity(vibrateIntensity), time(vibrateTime) {}
	~Vibration();

	// Member functions
	void Vibrate();

	bool getVibration() { return changeVibration; }
	void setVibrationMode(bool vibrationOn){ changeVibration = vibrationOn; }
private:
	// Member variables
	int time;
	int intensity;
	bool changeVibration;
};

extern Vibration* g_pVibration;

#endif  // __VIBRATION_H__