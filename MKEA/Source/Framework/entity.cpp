// COMP710 GP 2D Framework 2020

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pCurrentSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	// Set all Sprites to default
	assert(sprite);
	m_pCurrentSprite = sprite;
	m_pSpriteLight = sprite;
	m_pSpriteDark = sprite;

	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();

	SetIsLit(false);
	SetIsLightable(false);

	return (true);
}
bool
Entity::Initialise(Sprite* sprite, int x, int y)
{
	// Set all Sprites to default
	assert(sprite);
	m_pCurrentSprite = sprite;
	m_pSpriteLight = sprite;
	m_pSpriteDark = sprite;

	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();
	this->SetPosition(x, y);

	SetIsLit(false);
	SetIsLightable(false);

	return (true);
}

bool
Entity::SetSprites(Sprite* spriteLight, Sprite* spriteDark)
{
	// Set light and dark Sprites
	assert(spriteLight);
	m_pSpriteLight = spriteLight;

	assert(spriteDark);
	m_pSpriteDark = spriteDark;

	SetIsLit(true);
	SetIsLightable(true);

	return (true);
}

void Entity::ChangeSprites(Sprite * newSprite)
{
	// Switch current sprite 
	assert(newSprite);
	m_pCurrentSprite = newSprite;
	this->width = newSprite->GetWidth();
	this->height = newSprite->GetHeight();
}

void 
Entity::Process(float deltaTime)
{

}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pCurrentSprite);
	m_pCurrentSprite->SetX(static_cast<int>(m_x));
	m_pCurrentSprite->SetY(static_cast<int>(m_y));
	m_pCurrentSprite->Draw(backBuffer);
}

Sprite * Entity::GetDarkSprite()
{
	return m_pSpriteDark;
}

Sprite * Entity::GetLightSprite()
{
	return m_pSpriteLight;
}

bool
Entity::IsCollidingWith(Entity& e)
{
	bool colliding = false;
	if (e.m_pCurrentSprite != nullptr && m_pCurrentSprite != nullptr)
	{
		if (e.GetPositionY() + e.m_pCurrentSprite->GetHeight() > GetPositionY() && e.GetPositionY() < GetPositionY() + m_pCurrentSprite->GetHeight())
		{
			if (e.GetPositionX() + e.m_pCurrentSprite->GetWidth() > GetPositionX() && e.GetPositionX() < GetPositionX() + m_pCurrentSprite->GetWidth())
			{
				colliding = true;
			}
		}
	}
	

	return (colliding);
}

bool
Entity::IsCollidingWithYaxisRight(Entity& e)
{
	bool colliding = false;

	if (e.GetPositionY() + (e.m_pCurrentSprite->GetHeight())/3 > GetPositionY() && e.GetPositionY() < GetPositionY() + (m_pCurrentSprite->GetHeight())/3)
	{
		if (e.GetPositionX() + e.m_pCurrentSprite->GetWidth() > GetPositionX())
		{
			colliding = true;
		}
	}

	return (colliding);
}

bool
Entity::IsCollidingWithYaxisLeft(Entity& e)
{
	bool colliding = false;

	if (e.GetPositionY() + (e.m_pCurrentSprite->GetHeight()) / 3 > GetPositionY() && e.GetPositionY() < GetPositionY() + (m_pCurrentSprite->GetHeight()) / 3)
	{
		if (e.GetPositionX() < GetPositionX() + m_pCurrentSprite->GetWidth())
		{
			colliding = true;
		}
	}

	return (colliding);
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool Entity::IsDead() const
{
	return m_dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}
float Entity::GetPosition() 
{
	return m_x, m_y;
}
void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float 
Entity::GetPositionX() const
{
	return (m_x);
}

float 
Entity::GetPositionY() const
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

bool Entity::GetIsLit()
{
	return isLit;
}

void Entity::SetIsLit(bool lit)
{
	isLit = lit;
}

bool Entity::GetIsLightable()
{
	return isLightable;
}

void Entity::SetIsLightable(bool lightable)
{
	isLightable = lightable;
}
