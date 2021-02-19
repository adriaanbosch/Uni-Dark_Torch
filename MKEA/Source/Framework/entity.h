// COMP710 GP 2D Framework 2020
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);
	bool Initialise(Sprite* sprite, int x , int y);

	bool SetSprites(Sprite* spriteLight, Sprite* spriteDark);
	void ChangeSprites(Sprite* newSprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	Sprite* GetDarkSprite();
	Sprite* GetLightSprite();

	bool GetIsLit();
	void SetIsLit(bool lit);

	bool GetIsLightable();
	void SetIsLightable(bool lightable);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);
	bool IsCollidingWithYaxisLeft(Entity& e);
	bool IsCollidingWithYaxisRight(Entity& e);

	void SetPosition(float x, float y);
	float GetPosition();
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);


protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSpriteLight;
	Sprite* m_pSpriteDark;
	Sprite* m_pCurrentSprite;

	float width;
	float height;

	bool isLit;
	bool isLightable;

	bool hasGravity;
	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

private:

};

#endif //__ENTITY_H__
