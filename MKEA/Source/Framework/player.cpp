#include "player.h"
#include "backbuffer.h"



Player::Player()
	: movementSpeed(200)
	, jumpVelocity(20)
	, jumpHeight(17)
	, climbSpeed(120)
	, pressJump(false)
	, playerLive(3)
{
}


Player::~Player()
{
}

void
Player::playerMoveLeft(float deltaTime)
{
	float temp = Entity::GetPositionX() - movementSpeed * deltaTime;
	if (temp < 0)
	{
		temp = 0;
	}
	Entity::SetPositionX(temp);
}

void
Player::playerMoveRight(float deltaTime)
{
	float temp = Entity::GetPositionX() + movementSpeed * deltaTime;
	if (temp > 1870)
	{
		temp = 1870;
	}
	Entity::SetPositionX(temp);
}

void
Player::playerMoveUp(float deltaTime)
{
	float temp = Entity::GetPositionY() - climbSpeed * deltaTime;
	if (temp < 0)
	{
		temp = 0;
	}
	Entity::SetPositionY(temp);
}

void
Player::playerMoveDown(float deltaTime)
{
	float temp = Entity::GetPositionY() + climbSpeed * deltaTime;
	if (temp < 0)
	{
		temp = 0;
	}
	Entity::SetPositionY(temp);
}

void
Player::playerJump(float deltaTime)
{
	if (pressJump)
	{
		jumpHeight = jumpHeight - jumpVelocity * deltaTime;
		if (jumpHeight <0)
		{
			jumpHeight = 17;
			pressJump = false;
		}
		Entity::SetPositionY(Entity::GetPositionY() - jumpHeight);
	}
}

void
Player::setPressJump(bool playerJump)
{
	pressJump = playerJump;
}
