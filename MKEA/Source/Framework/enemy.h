#pragma once
#include "entity.h"
#include "bullet.h"
#include "player.h"
class Enemy : public Entity
{
public: //methods
	Enemy();
	~Enemy();
	Enemy(float hp, float spd, float dmg, int x, int y);
	void Process(float deltaTime, Player* player);
	bool searchPlayer(float deltaTime, Player * player, float radius);
	bool shootPlayer(float deltaTime, Player * player, float radius);
	bool getLit();
	void setLit(bool light);
	void setGrounded(bool input);
protected:

private:

public: // data members
	 
protected:
	Sprite* sprite;
	float lastShot;
	float health;
	float speed;
	float damage;
	bool isDead;
	bool isLit;
	bool onGround;
private:
};

