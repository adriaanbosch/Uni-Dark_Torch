#include "enemy.h"
#include "logmanager.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(float hp, float spd, float dmg, int x, int y)
{
	health = hp;
	speed = spd;
	damage = dmg;
	isDead = false;
	onGround = true;
	
}

void Enemy::Process(float deltaTime, Player* player)
{
	float temp;
	if (player->GetPositionX() < this->GetPositionX())
	{
		temp = (this->GetPositionX() - speed * deltaTime);
		this->SetPosition(temp, this->GetPositionY());
	}
	else if (player->GetPositionX() > this->GetPositionX())
	{
		temp = (this->GetPositionX() + speed * deltaTime);
		this->SetPosition(temp, this->GetPositionY());
	}

	if (player->GetPositionY() < this->GetPositionY())
	{
		temp = (this->GetPositionY() - speed * deltaTime);
		this->SetPosition(this->GetPositionX(), temp);
	}
	else if (player->GetPositionY() > this->GetPositionY())
	{
		temp = (this->GetPositionY() + speed * deltaTime);
		this->SetPosition(this->GetPositionX(), temp);
	}
}

bool Enemy::searchPlayer(float deltaTime, Player* player, float radius)
{
	float playerX = player->GetPositionX();
	float playerY = player->GetPositionY();
		
	if (((playerX - m_x)*(playerX - m_x) + (playerY - m_y)*(playerY - m_y)) < radius*radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::shootPlayer(float deltaTime, Player* player, float radius)
{
	lastShot += deltaTime;//this doesnt work

	if (lastShot > 5)
	{
		float playerX = player->GetPositionX();
		float playerY = player->GetPositionY();

		if (((playerX - m_x)*(playerX - m_x) + (playerY - m_y)*(playerY - m_y)) < radius*radius)
		{
			lastShot = 0;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Enemy::getLit()
{
	return isLit;
}

void Enemy::setLit(bool light)
{
	isLit = light;
}

void Enemy::setGrounded(bool input)
{
	onGround = input;
}


