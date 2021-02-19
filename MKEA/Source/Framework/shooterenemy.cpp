#include "shooterenemy.h"



ShooterEnemy::ShooterEnemy()
{
}

ShooterEnemy::ShooterEnemy(float hp, float spd, float dmg, int x, int y)
{
	health = hp;
	speed = spd;
	damage = dmg;
	isDead = false;
	onGround = true;
	lastShot = 0;
	this->SetPosition(x, y);
}


ShooterEnemy::~ShooterEnemy()
{
}
