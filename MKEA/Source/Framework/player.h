#pragma once
#include"entity.h"
#include"sprite.h"
class BackBuffer;

class Player : public Entity
{
public:
	Player();
	~Player();
	void playerMoveLeft(float deltaTime);
	void playerMoveUp(float deltaTime);
	void playerMoveDown(float deltaTime);
	void playerMoveRight(float deltaTime);
	void playerJump(float deltaTime);
	void setPressJump(bool playerJump);
protected:

private:

public: // data members
	int playerLive;

protected:
	float movementSpeed;
	float jumpVelocity;
	float jumpHeight;
	float climbSpeed;
	bool pressJump;
private:
};

