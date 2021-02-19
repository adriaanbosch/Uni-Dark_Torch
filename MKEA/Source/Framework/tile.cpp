#include "tile.h"



Tile::Tile(int positionx, int positiony, int tiletype, bool solid)
	: positionX(0)
	, positionY(0)
	, tileType(0)
	, isSolid(false)
{
	positionX = positionx;
	positionY = positiony;
	tileType = tiletype;
	isSolid = solid;
	Entity::Entity();
}
Tile::Tile()
{
	Entity::Entity();
}

Tile::~Tile()
{
}
bool Tile::Initialise(Sprite* sprite) 
{

	return Entity::Initialise(sprite, positionX, positionY);
	
}
void
Tile::Draw(BackBuffer& backBuffer)
{
	Entity::Draw(backBuffer);
}
void Tile::SetIsLit(bool i) 
{
	isLit = i;
}
int Tile::GetTileType() 
{
	return tileType;
}
void Tile::SetTileType(int type)
{
	tileType = type;
}
int Tile::GetPositionX()
{
	return positionX;
}
int Tile::GetPositionY()
{
	return positionY;
}
bool Tile::GetIsSolid() 
{
	return isSolid;
}