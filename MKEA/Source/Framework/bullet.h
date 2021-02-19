#pragma once
#include"entity.h"
class Bullet : public Entity
{
public:
	Bullet();
	Bullet(float x, float y, float spd);
	~Bullet();
	void Process(float deltaTime);
protected:

private:

public: // data members

protected:
	float lifespan;
	float targetX;
	float targetY;
	float speed;
private:
};

