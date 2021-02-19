#pragma once
#include <SDL.h>
#include "entity.h"
class Torch : public Entity
{
public:
	Torch();
	~Torch();

	void Process(float deltaTime);

	bool GetTorchOn();
	void SetTorchOn(bool t);

	float GetRadius();
	void SetRadius(float radius);

	float GetBatteryLevel();
	void SetBatteryLevel(float b);
	float GetDepleteRate();
	void SetDepleteRate(float d);
	float GetRestoreRate();
	void SetRestoreRate(float r);
	float GetMaxBattery();
	void SetMaxBattery(float m);

private:
	bool torchOn;
	float batteryLevel;
	float maxBattery;
	float depleteRate;
	float restoreRate;
	float lightRadius;
};

