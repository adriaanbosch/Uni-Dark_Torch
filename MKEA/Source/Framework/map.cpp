#include "map.h"

#include "tile.h"
#include "sprite.h"
#include "backbuffer.h"
#include <vector>
Map::Map()
{
	// Set Tile Dimensions
	tileHeight = 50;
	tileWidth = 50;
}
Map::~Map()
{
}
bool Map::Initialise(Sprite* sprite)
{
	return Entity::Initialise(sprite);
}

// this method simply checks the value of level and assigns that level int array to map variable and returns it
void Map::AssignMapLevel() 
{
	switch (level)
	{
	case 0:
		map = map0;
		//return map0;
		break;
	case 1:
		map = map1;
		break;
	case 2:
		map = map2;
		break;
	case 3:
		map = map3;
		break;
	case 4:
		map = map4;
		break;
	default:
		break;
	}
}
void Map::LoadMap(std::vector<Tile*>* tileMap)
{
	AssignMapLevel();
	Tile* isTile;
	int tileType = 0;
	for (int row = 0; row < 21; row++)
	{
		for (int column = 0; column < 38; column++)
		{
			tileType = map[row][column];
			positionX = column * GetTileWidth();
			positionY = row * GetTileHeight();

			switch (tileType)
			{
				// Tiles
			case 0: // nothing
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 1: // normal tile
				isTile = new Tile(positionX, positionY, tileType, true);
				break;
			case 2:
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 3:
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 4:
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 5:
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 6:
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 7:
				isTile = new Tile(positionX, positionY, tileType, true);
				break;
			case 8:
				isTile = new Tile(positionX, positionY, tileType, true);
				break;
			case 9://enemySpawn
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			case 10:
				isTile = new Tile(positionX, positionY, tileType, false);
				break;
			}
			tileMap->push_back(isTile);
		}
	}
}
int Map::GetLevel()
{
	return level;
}

void Map::SetLevel(int lvl)
{
	level= lvl;
}
float Map::GetTileHeight() 
{
	return tileHeight;
}
float Map::GetTileWidth() 
{
	return tileWidth;
}