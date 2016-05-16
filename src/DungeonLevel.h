#include <vector>
#include <iostream>
#include <random>
#include "Tile.h"

#ifndef _DungeonLevel_included_
#define _DungeonLevel_included_

class DungeonLevel
{
public:
	DungeonLevel();
	~DungeonLevel();

	bool unitTestReqs(bool bl_Display);
	void initLevel();
	void displayLevel();
	int getWidth();
	int getHeight();
	char at(int x, int y);
	std::vector<std::vector<Tile> > getTileVector();
	void setTileVector(std::vector<std::vector<Tile> > vec);
private:
	//private functions
	void createRoom();
	void createTunnels();
	void createStairs();
	void createDoorway(int int_X, int int_Y, int int_Height, int int_Width, int &int_YWall, int &int_XWall);
	bool noRoom(int intX, int intY, int intWidth, int intHeight);
	bool destinationReached(int posX, int posY, int endX, int endY);
	void checkRooms(std::vector<std::vector<char> > & vec_TempTiles, int tempX, int tempY);

	//determines how to get around a room
	int wayAroundX(int int_X, int int_Y, int upDown, int leftRight);
	int wayAroundY(int int_X, int int_Y, int leftRight, int upDown);

	//determines which side of the room the door is one
	void doorSide(int &posX, int &posY, int doorX, int doorY, int currentRoom);

	//determines which way to tunnel based on where doors are
	int tunnelLeft(int posX, int &posY, int endX, int endY);
	int tunnelRight(int posX, int &posY, int endX, int endY);
	int tunnelUp(int &posX, int posY, int endX, int endY);
	int tunnelDown(int &posX, int posY, int endX, int endY);

	//private variables
	std::vector<std::vector<char> > vec_Level;		//stores entire level
	std::vector<std::vector<int> > vec_Rooms;		//stores each room X, Y, Width, and Height, overlaps another room
	std::vector<std::vector<Tile> > vec_LevelTiles;	//stores the Tiles for the level
	bool bl_Up;
	bool bl_Down;
	int int_MaxTiles;
	int int_Tiles;
	int int_LevelWidth;
	int int_LevelHeight;
	std::mt19937 mt;
};

#endif