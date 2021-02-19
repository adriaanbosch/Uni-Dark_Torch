#include "bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(float x, float y, float spd)
{
	lifespan = 0;
	targetX = x;
	targetY = y;
	speed = spd;
}

Bullet::~Bullet()
{
}

void
Bullet::Process(float deltaTime)
{
	lifespan += deltaTime;
	if (lifespan > 10)
	{
		SetDead(true);
	}
	float temp;
	if (targetX < this->GetPositionX())
	{
		temp = (this->GetPositionX() - speed * deltaTime);
		this->SetPosition(temp, this->GetPositionY());
	}
	else if (targetX > this->GetPositionX())
	{
		temp = (this->GetPositionX() + speed * deltaTime);
		this->SetPosition(temp, this->GetPositionY());
	}

	if (targetY < this->GetPositionY())
	{
		temp = (this->GetPositionY() - speed * deltaTime);
		this->SetPosition(this->GetPositionX(), temp);
	}
	else if (targetY > this->GetPositionY())
	{
		temp = (this->GetPositionY() + speed * deltaTime);
		this->SetPosition(this->GetPositionX(), temp);
	}
}
