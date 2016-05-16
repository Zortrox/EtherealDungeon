#include "DungeonLevel.h"
#include <time.h>

using namespace std;

DungeonLevel::DungeonLevel()
{
	initLevel();
}

DungeonLevel::~DungeonLevel()
{

}

int DungeonLevel::getWidth()
{
	return int_LevelWidth;
}
int DungeonLevel::getHeight()
{
	return int_LevelHeight;
}
char DungeonLevel::at(int x, int y)
{
	return vec_Level.at(y).at(x);
}

vector<vector<Tile> > DungeonLevel::getTileVector()
{
	return vec_LevelTiles;
}

void DungeonLevel::setTileVector(vector<vector<Tile> > vec)
{
	vec_LevelTiles = vec;
}

//initialize level for rooms, stairs, and tunnels
void DungeonLevel::initLevel()
{
	do
	{
		int loopNum = 0;
		mt.seed( (unsigned long)time(NULL) );
		int_MaxTiles = 200 + mt()%151;
		int_Tiles = 0;
		bl_Up = false;
		bl_Down = false;
		int_LevelWidth = 79;
		int_LevelHeight = 20;

		vec_LevelTiles.resize(int_LevelHeight);
		for (int i = 0; i < int_LevelHeight; i++)
		{
			vec_LevelTiles.at(i).resize(int_LevelWidth);
		}

		vec_Level.resize(int_LevelHeight);
		for (int i = 0; i < int_LevelHeight; i++)
		{
			vec_Level.at(i).resize(int_LevelWidth, ' ');
		}

		while (int_Tiles < int_MaxTiles && loopNum < 200)
		{
			createRoom();
			loopNum++;
		}
	
		createTunnels();
		createStairs();
		unitTestReqs(false);
	}
	while (unitTestReqs(false) == false);
}

//output all level data for unit test
bool DungeonLevel::unitTestReqs(bool bl_Display)
{
	bool bl_ReqsMet = true;

	if (int_Tiles < 200 || bl_Up == false || bl_Down == false)
	{
		bl_ReqsMet = false;
	}
	if (bl_Display)
	{
		cout << "	Level Width:  " << int_LevelWidth << endl;
		cout << "	Level Height: " << int_LevelHeight << endl;
		cout << "	Tiles Used:   " << int_Tiles << endl;
		cout << "	Upstairs:        " << boolalpha << bl_Up << endl;
		cout << "	Downstairs:      " << boolalpha << bl_Down << endl;
	}

	bool bl_Connected = true;
	vector<vector<char> > vec_TempTiles = vec_Level;
	checkRooms(vec_TempTiles, vec_Rooms.at(0).at(0) + 1, vec_Rooms.at(0).at(1) + 1); //starts at room 1
	for (size_t i = 0; i < vec_TempTiles.size(); i++)
	{
		for (size_t j = 0; j < vec_TempTiles.at(i).size(); j++)
		{
			if (vec_TempTiles.at(i).at(j) != 'X' && vec_TempTiles.at(i).at(j) != ' ' &&
			vec_TempTiles.at(i).at(j) != '-' && vec_TempTiles.at(i).at(j) != '|')
			{
				bl_ReqsMet = false;
				bl_Connected = false;
			}
		}
	}
	if (bl_Display)
	{
		cout << "	Rooms Connected: " << boolalpha << bl_Connected << endl;
	}

	for (size_t i = 0; i < vec_Rooms.size(); i++)	//iterates through each room
	{
		if (vec_Rooms.at(i).at(4) == 1 || (vec_Rooms.at(i).at(3) * vec_Rooms.at(i).at(2) < 16))
		{
			bl_ReqsMet = false;
		}
		if (bl_Display)
		{
			cout << "	Room " << i+1 << " Size: " << vec_Rooms.at(i).at(3) * vec_Rooms.at(i).at(2) << endl;
			cout << "	Room " << i+1 << " Overlaps: " << boolalpha << vec_Rooms.at(i).at(4) << endl;
		}
	}

	return bl_ReqsMet;
}

//checks whether entire level is tunneled and connected
void DungeonLevel::checkRooms(std::vector<std::vector<char>> &vec_TempTiles, int tempX, int tempY)
{
	if (tempX < int_LevelWidth && tempX >= 0 && tempY < int_LevelHeight && tempY >= 0)
	{
		if (vec_TempTiles.at(tempY).at(tempX) != 'X' && (vec_TempTiles.at(tempY).at(tempX) == '.' ||
			vec_TempTiles.at(tempY).at(tempX) == '#' || vec_TempTiles.at(tempY).at(tempX) == '<' || vec_TempTiles.at(tempY).at(tempX) == '>'))
		{
			vec_TempTiles.at(tempY).at(tempX) = 'X';
			checkRooms(vec_TempTiles, tempX+1, tempY);
			checkRooms(vec_TempTiles, tempX-1, tempY);
			checkRooms(vec_TempTiles, tempX, tempY+1);
			checkRooms(vec_TempTiles, tempX, tempY-1);
		}
	}
}

//create room with floor and walls
void DungeonLevel::createRoom()
{
	int int_randX = mt() % int_LevelWidth;	//sets a starting X point for the room (top left corner of room)
	int int_randY = mt() % int_LevelHeight;	//sets a starting Y point for the room (top left corner of room)
	int int_Width = mt()%11+4;	//room width between 4 and 16
	int int_Height = mt()%5+4;	//room height between 4 and 8

	//so rooms don't extend beyond level
	while (int_randX+int_Width > int_LevelWidth)
	{
		int_randX = mt() % int_LevelWidth;
		int_Width = mt()%11+4;
	}
	while (int_randY+int_Height > int_LevelHeight)
	{
		int_randY = mt() % int_LevelHeight;
		int_Height = mt()%5+4;
	}

	if (noRoom(int_randX, int_randY, int_Width, int_Height))
	{

		for (int i = int_randY; i < int_randY+int_Height; i++)
		{
			for (int j = int_randX; j < int_randX+int_Width; j++)
			{
				if (i == int_randY || i == int_randY+int_Height-1)
				{
					vec_Level.at(i).at(j) = '-';
					int_Tiles++;
				}
				else if (j == int_randX || j == int_randX+int_Width-1)
				{
					vec_Level.at(i).at(j) = '|';
					int_Tiles++;
				}
				else
				{
					vec_Level.at(i).at(j) = '.';
					int_Tiles++;
				}
			}
		}

		//put room dimensions in vector
		int int_newVecSize = vec_Rooms.size();
		vec_Rooms.resize(int_newVecSize + 1);
		vec_Rooms.at(int_newVecSize).push_back(int_randX);
		vec_Rooms.at(int_newVecSize).push_back(int_randY);
		vec_Rooms.at(int_newVecSize).push_back(int_Width);
		vec_Rooms.at(int_newVecSize).push_back(int_Height);
		vec_Rooms.at(int_newVecSize).push_back(0);		//whether room overlaps another room
	}
}

//display level to console
void DungeonLevel::displayLevel()
{
	for (int i = 0; i < int_LevelHeight; i++)
	{
		for (int j = 0; j < int_LevelWidth; j++)
		{
			cout << vec_Level.at(i).at(j);
		}
		cout << endl;
	}
}

//checks whether a room exists at new room's position
bool DungeonLevel::noRoom(int intX, int intY, int intWidth, int intHeight)
{
	//to determine whether there will be a 3 wide gap between rooms
	int tempY = intY - 3;
	if (tempY < 0) tempY = 0;
	int tempX = intX - 3;
	if (tempX < 0) tempX = 0;

	int tempWidth = tempX + intWidth + 6;	//+6 to compensate for -3 on X
	if (tempWidth > int_LevelWidth) tempWidth = int_LevelWidth;
	int tempHeight = tempY + intHeight + 6;	//+2 to compensate for -3 on Y
	if (tempHeight > int_LevelHeight) tempHeight = int_LevelHeight;

	if (vec_Level.at(intY).at(intX) != ' ')
	{
		return false;
	}

	for (int i = tempY; i < tempHeight; i++)
	{
		for (int j = tempX; j < tempWidth; j++)
		{
			if (vec_Level.at(i).at(j) != ' ')
			{
				return false;
			}
		}
	}

	return true;
}

void DungeonLevel::createTunnels()
{
	//to keep track of current tunnel tile
	int posX = 0;
	int posY = 0;

	int endX = 0;
	int endY = 0;

	for (size_t i = 0; i < vec_Rooms.size(); i++)
	{
		int int_roomNum = mt()%vec_Rooms.size();

		while (int_roomNum == i)
		{
			int_roomNum = mt()%vec_Rooms.size();
		}

		posX = 0;
		posY = 0;
		endX = 0;
		endY = 0;

		int int_doorX1 = 0;
		int int_doorY1 = 0;
		int int_doorX2 = 0;
		int int_doorY2 = 0;

		createDoorway(vec_Rooms.at(i).at(0), vec_Rooms.at(i).at(1), vec_Rooms.at(i).at(3), vec_Rooms.at(i).at(2), int_doorY1, int_doorX1);
		createDoorway(vec_Rooms.at(int_roomNum).at(0), vec_Rooms.at(int_roomNum).at(1), vec_Rooms.at(int_roomNum).at(3), vec_Rooms.at(int_roomNum).at(2), int_doorY2, int_doorX2);

		//insert door
		vec_Level.at(int_doorY1).at(int_doorX1) = '.';
		vec_Level.at(int_doorY2).at(int_doorX2) = '.';

		//start tunneling ----------------------------------------------------------------------
		doorSide(posX, posY, int_doorX1, int_doorY1, i);
		doorSide(endX, endY, int_doorX2, int_doorY2, int_roomNum);

		while (!destinationReached(posX, posY, endX, endY))
		{
			if (mt()%2 < 1)
			{
				//tunnel left
				if (posX > endX)
				{
					posX = tunnelLeft(posX, posY, endX, endY);
					vec_Level.at(posY).at(posX) = '#';
				}
				//tunnel right
				else if (posX < endX)
				{
					posX = tunnelRight(posX, posY, endX, endY);
					vec_Level.at(posY).at(posX) = '#';
				}
			}
			else
			{
				//tunnel up
				if (posY > endY)
				{
					posY = tunnelUp(posX, posY, endX, endY);
					vec_Level.at(posY).at(posX) = '#';
				}
				//tunnel down
				else if (posY < endY)
				{
					posY = tunnelDown(posX, posY, endX, endY);
					vec_Level.at(posY).at(posX) = '#';
				}
			}
		}
	}
}

//create doorway for tunnels to connect to
void DungeonLevel::createDoorway(int int_X, int int_Y, int int_Height, int int_Width, int &int_YWall, int &int_XWall)
{
	//no edge doorways
	while (int_YWall == 0 || int_YWall == int_LevelHeight - 1)
	{
		int_YWall = mt()%int_Height+int_Y;	//pick random wall from height
	}
	if (int_YWall == int_Y || int_YWall == int_Y+int_Height-1)
	{
		//no edge doorways & no corners
		while (int_XWall == 0 || int_XWall == int_LevelWidth-1 || int_XWall == int_X || int_XWall == int_X+int_Width-1)
		{
			int_XWall = mt()%(int_Width)+(int_X);	//pick random wall from width
		}
	}
	else
	{
		//either left or right wall
		if (mt()%2 == 0)
		{
			if (int_X == 0)
			{
				int_XWall = int_X+int_Width-1;
			}
			else
			{
				int_XWall = int_X;
			}
		}
		else
		{
			if (int_X+int_Width-1 == int_LevelWidth - 1)
			{
				int_XWall = int_X;
			}
			else
			{
				int_XWall = int_X+int_Width-1;
			}
		}
	}
}

//to find a way around room using the X-axis
int DungeonLevel::wayAroundX(int int_X, int int_Y, int upDown, int leftRight)
{
	int tempX = int_X;
	if ((mt()%2 == 0 || (leftRight < 0 && mt()%3 < 2)))
	{
		while (vec_Level.at(int_Y + upDown).at(tempX) != ' ' && vec_Level.at(int_Y + upDown).at(tempX) != '#')
		{
			tempX--;
			if (tempX < 0)
			{
				tempX++;
				while (vec_Level.at(int_Y + upDown).at(tempX) != ' ' && vec_Level.at(int_Y + upDown).at(tempX) != '#')
				{
					tempX++;
				}
			}
		}
	}
	else
	{
		while (vec_Level.at(int_Y + upDown).at(tempX) != ' ' && vec_Level.at(int_Y + upDown).at(tempX) != '#')
		{
			tempX++;
			if (tempX >= int_LevelWidth)
			{
				tempX--;
				while (vec_Level.at(int_Y + upDown).at(tempX) != ' ' && vec_Level.at(int_Y + upDown).at(tempX) != '#')
				{
					tempX--;
				}
			}
		}
	}

	if (tempX < int_X)
	{
		for (int i = int_X; i > tempX; i--)
		{
			vec_Level.at(int_Y).at(i) = '#';
		}
	}
	else
	{
		for (int i = int_X; i < tempX; i++)
		{
			vec_Level.at(int_Y).at(i) = '#';
		}
	}

	return tempX;
}

//to find a way around room using the Y-axis
int DungeonLevel::wayAroundY(int int_X, int int_Y, int leftRight, int upDown)
{
	int tempY = int_Y;
	if ((mt()%2 == 0 || (upDown < 0 && mt()%3 < 2)))
	{
		while (vec_Level.at(tempY).at(int_X + leftRight) != ' ' && vec_Level.at(tempY).at(int_X + leftRight) != '#')
		{
			tempY--;
			if (tempY < 0)
			{
				tempY++;
				while (vec_Level.at(tempY).at(int_X + leftRight) != ' ' && vec_Level.at(tempY).at(int_X + leftRight) != '#')
				{
					tempY++;
				}
			}
		}
	}
	else
	{
		while (vec_Level.at(tempY).at(int_X + leftRight) != ' ' && vec_Level.at(tempY).at(int_X + leftRight) != '#')
		{
			tempY++;
			if (tempY >= int_LevelHeight)
			{
				tempY--;
				while (vec_Level.at(tempY).at(int_X + leftRight) != ' ' && vec_Level.at(tempY).at(int_X + leftRight) != '#')
				{
					tempY--;
				}
			}
		}
	}

	if (tempY < int_Y)
	{
		for (int i = int_Y; i > tempY; i--)
		{
			vec_Level.at(i).at(int_X) = '#';
		}
	}
	else
	{
		for (int i = int_Y; i < tempY; i++)
		{
			vec_Level.at(i).at(int_X) = '#';
		}
	}

	return tempY;
}

//has destination been reached
bool DungeonLevel::destinationReached(int posX, int posY, int endX, int endY)
{
	//if tunnel is adjacent to doorway
	if (posX == endX && posY == endY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//create upstairs and downstairs
void DungeonLevel::createStairs()
{
	int doorRoom = -1;

	for (int i = 0; i < 2; i++)
	{
		int stairX = 0;
		int stairY = 0;
		int int_RoomNum = mt()%vec_Rooms.size();

		while (doorRoom == int_RoomNum)
		{
			int_RoomNum = mt()%vec_Rooms.size();
		}

		stairX = mt()%(vec_Rooms.at(int_RoomNum).at(2)-2) + (vec_Rooms.at(int_RoomNum).at(0)+1);
		stairY = mt()%(vec_Rooms.at(int_RoomNum).at(3)-2) + (vec_Rooms.at(int_RoomNum).at(1)+1);

		if (!bl_Up)
		{
			vec_Level.at(stairY).at(stairX) = '<';
			bl_Up = true;
		}
		else if (!bl_Down)
		{
			vec_Level.at(stairY).at(stairX) = '>';
			bl_Down = true;
		}

		doorRoom = int_RoomNum;
	}
}

//logic for tunnel to tunnel left
int DungeonLevel::tunnelLeft(int posX, int &posY, int endX, int endY)
{
	do
	{
		vec_Level.at(posY).at(posX) = '#';

		if (posX > 0)
		{		
			if (vec_Level.at(posY).at(posX-1) == ' ' || vec_Level.at(posY).at(posX-1) == '#')
			{
				posX--;
			}
			else
			{
				posY = wayAroundY(posX, posY, -1, endY-posY);
			}
		}
	}
	while (!destinationReached(posX, posY, endX, posY));

	vec_Level.at(posY).at(posX) = '#';

	return posX;
}

//logic for tunnel to tunnel right
int DungeonLevel::tunnelRight(int posX, int &posY, int endX, int endY)
{
	do
	{
		vec_Level.at(posY).at(posX) = '#';

		if (posX < int_LevelWidth - 1)
		{
			if (vec_Level.at(posY).at(posX+1) == ' ' || vec_Level.at(posY).at(posX+1) == '#')
			{
				posX++;
			}
			else
			{
				posY = wayAroundY(posX, posY, +1, endY-posY);
			}
		}
	}
	while (!destinationReached(posX, posY, endX, posY));

	vec_Level.at(posY).at(posX) = '#';

	return posX;
}

//logic for tunnel to tunnel up
int DungeonLevel::tunnelUp(int &posX, int posY, int endX, int endY)
{
	do
	{
		vec_Level.at(posY).at(posX) = '#';

		if (posY > 0)
		{
		
			if (vec_Level.at(posY-1).at(posX) == ' ' || vec_Level.at(posY-1).at(posX) == '#')
			{
				posY--;
			}
			else
			{
				posX = wayAroundX(posX, posY, -1, endX-posX);
			}
		}
	}
	while (!destinationReached(posX, posY, posX, endY));

	vec_Level.at(posY).at(posX) = '#';

	return posY;
}

//logic for tunnel to tunnel down
int DungeonLevel::tunnelDown(int &posX, int posY, int endX, int endY)
{
	do
	{
		vec_Level.at(posY).at(posX) = '#';

		if (posY < int_LevelHeight - 1)
		{
			if (vec_Level.at(posY+1).at(posX) == ' ' || vec_Level.at(posY+1).at(posX) == '#')
			{
				posY++;
			}
			else
			{
				posX = wayAroundX(posX, posY, +1, endX-posX);
			}
		}
	}
	while (!destinationReached(posX, posY, posX, endY));

	vec_Level.at(posY).at(posX) = '#';

	return posY;
}

//checks which side of the room a door appears on
void DungeonLevel::doorSide(int &posX, int &posY, int doorX, int doorY, int currentRoom)
{
	//if top door
	if (doorY == vec_Rooms.at(currentRoom).at(1))
	{
		posX = doorX;
		posY = doorY - 1;
	}
	//if bottom door
	else if (doorY == (vec_Rooms.at(currentRoom).at(1) + vec_Rooms.at(currentRoom).at(3) - 1))
	{
		posX = doorX;
		posY = doorY + 1;
	}
	//if left door
	else if (doorX == vec_Rooms.at(currentRoom).at(0))
	{
		posX = doorX - 1;
		posY = doorY;
	}
	//if right door
	else if (doorX == (vec_Rooms.at(currentRoom).at(0) + vec_Rooms.at(currentRoom).at(2) - 1))
	{
		posX = doorX + 1;
		posY = doorY;
	}
}