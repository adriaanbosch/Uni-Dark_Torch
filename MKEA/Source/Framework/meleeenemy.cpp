#include "meleeenemy.h"



MeleeEnemy::MeleeEnemy(float hp, float spd, float dmg, int x, int y)
{
	health = hp;
	speed = spd;
	damage = dmg;
	isDead = false;
	onGround = true;
	this->SetPosition(x, y);
}


MeleeEnemy::~MeleeEnemy()
{
}
