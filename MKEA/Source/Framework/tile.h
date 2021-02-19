#pragma once
#include"entity.h"
class Tile : public Entity
{
public:
	Tile();
	Tile(int, int, int, bool);
	~Tile();
	bool Initialise(Sprite* sprite);
	void Draw(BackBuffer& backBuffer);
	void SetIsLit(bool);
	int GetTileType();
	void SetTileType(int type);
	int GetPositionX();
	int GetPositionY();
	bool GetIsSolid();
protected:

private:

public: // data members
	

protected:

private:
	int positionX;
	int positionY;
	bool isSolid;
	bool isLit;
	int tileType;
};

