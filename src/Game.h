#pragma once

#ifndef _Game_included_
#define _Game_included_

#include <curses.h>
#include <string>
#include <vector>
#include <list>

#include "DungeonLevel.h"
#include "Player.h"
#include "Tile.h"
#include "Potion.h"
#include "CreatureFactory.h"
#include "ItemFactory.h"
#include "Node.h"

class Game{
public:
	Game();
	virtual ~Game();
	
	bool playAgain();
	//getters & setters

protected:

private:
	//functions
	void init_Level();
	void createNewLevel();
	void reset_Level();
	void changeLevel(int changeAmount);
	void Command();
	void redrawScreen();
	void drawStats();
	void drawMessages();
	void drawPlayer();
	void drawCreatures();
	void drawItems();
	void drawDungeon();
	void takeTurn();
	void monsterTurn();
	void moveCreature(Creature* &creature, int X, int Y);
	void spawnMonster();
	void playerAttack(int monsterX, int monsterY);
	void playerMove(int playerNewX, int playerNewY, bool &TakenAction);
	void outputText(std::string str_Message, int beginX, int beginY);
	std::string itemArticleName(Item* &tempItem);
	void displayItems(int currentTab, bool &TakenAction);
	void setTilesVisible(std::vector<std::vector<char> > &vec_TempTiles, int x, int y, int direction, int range);
	void setTilesInvisible(std::vector<std::vector<char> > &vec_TempTiles);
	void pickupItem(Item* &tempItem, int vecPos, bool &TakenAction);
	void tossItem(Item* &tempItem, int vecPos, bool &TakenAction);
	void equipItem(Item* &tempItem, int vecPos, int itemLocation, bool &TakenAction);
	void useItem(Item* &tempItem, int vecPos, int itemLocation, bool &TakenAction);
	void etherealDeath();

	void startScreen();
	void characterLevelUp(std::string characterType, int skillPoints);	//new, current
	int popupMessage(std::string strMessage, std::vector<std::string> vec_ChoiceNames, int defaultSelection, bool bTextbox, std::string &strResponse, int maxTextLength);

	//player variables
	Player player;
	int playerLevel;

	//game variables
	WINDOW * curWin;
	std::vector<DungeonLevel*> vec_Levels;
	std::string strLevelName;
	std::vector<std::vector<Tile> > vec_Tiles;
	std::vector<std::vector<char> > vec_CharTiles;
	int intCurrentLevel;
	CreatureFactory cFac;
	ItemFactory iFac;
	char char_Button;
	std::mt19937 mt;
	unsigned long long lngTurns;
	long score;
	bool restart;
	bool gameOver;
	bool etherealMode;

	//messages
	std::vector<std::string> vec_Messages;
	std::string str_Update;
	int oldMessageSize;
	bool newUpdate;
	int intCurrentMessageLine;
	std::vector<std::string> vec_Options;
	chtype msgSelectionColor;
	std::string strNOMESSAGE;

	//pathing
	std::list<Node*> list_OpenNodes;
	std::list<Node*> list_ClosedNodes;
	std::list<Node*> list_Path;
	bool PathFound;
};

#endif