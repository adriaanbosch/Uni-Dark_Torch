#include "torch.h"

Torch::Torch()
{
	SetTorchOn(false);
	SetBatteryLevel(100);
	SetMaxBattery(100);
	SetDepleteRate(8);
	SetRestoreRate(3);
	SetRadius(200);
}

Torch::~Torch()
{
}

void Torch::Process(float deltaTime)
{
	// Keep Torch on Mouse
	int mouseX;
	int mouseY;
	SDL_GetGlobalMouseState(&mouseX, &mouseY);

	SetPositionX(mouseX);
	SetPositionY(mouseY);
	
	// Manage Battery
	if (GetTorchOn())
	{
		SetBatteryLevel(GetBatteryLevel() - (depleteRate * deltaTime));
	}
	else
	{
		if (GetBatteryLevel() < GetMaxBattery())
		{
			SetBatteryLevel(GetBatteryLevel() + (restoreRate * deltaTime));
		}
	}
}

bool Torch::GetTorchOn()
{
	return torchOn;
}

void Torch::SetTorchOn(bool t)
{
	torchOn = t;
}

float Torch::GetRadius()
{
	return lightRadius;
}

void Torch::SetRadius(float radius)
{
	lightRadius = radius;
}

float Torch::GetBatteryLevel()
{
	return batteryLevel;
}

void Torch::SetBatteryLevel(float b)
{
	batteryLevel = b;
}

float Torch::GetDepleteRate()
{
	return depleteRate;
}

void Torch::SetDepleteRate(float d)
{
	depleteRate = d;
}

float Torch::GetRestoreRate()
{
	return restoreRate;
}

void Torch::SetRestoreRate(float r)
{
	restoreRate = r;
}

float Torch::GetMaxBattery()
{
	return maxBattery;
}

void Torch::SetMaxBattery(float m)
{
	maxBattery = m;
}
