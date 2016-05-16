#pragma once

#ifndef _Player_included_
#define _Player_included_

#include "Creature.h"
#include "Tile.h"
#include <vector>

class Player: public Creature {
public:
	Player();
	virtual ~Player();

	bool canMove(int x, int y, std::vector<std::vector<Tile> > &vec_TempTiles);
	void setPlayerLevels(unsigned long long lngTurns);
	int lanternSight();
	void lanternState();		//changes lantern state
	bool hasLantern();
	bool lanternOut();

	//getters and setters
	std::string getRank();
	int getStr();
	int getDex();
	int getCon();
	int getInt();
	int getWis();
	int getCha();
	int getMana();
	int getMaxMana();
	int getAC();
	int getExPoints();
	int getHunger();
	int getAlign();

	void setRank(std::string Rank);
	void setStr(int Str);
	void setDex(int Dex);
	void setCon(int Con);
	void setInt(int Int);
	void setWis(int Wis);
	void setCha(int Cha);
	void setMana(int Mana);
	void setMaxMana(int MaxMana);
	void setAC(int AC);
	void setExPoints(int ExPoints);
	void setHunger(int Hunger);
	void setAlign(int Align);

	int getOil();
	void setOil(int oil);

	int getGold();
	void setGold(int gold);

	int getETurns();
	void setETurns(int turns);
	int getMaxETurns();
	void setMaxETurns(int turns);
protected:

private:
	int oilLevel;
	bool bLanternOut;
	bool bHasLantern;
	int intGold;
	int etherealTurns;
	int maxEtherealTurns;

	std::string strRank;
	int intStr;
	int intDex;
	int intCon;
	int intInt;		//Hahaha
	int intWis;
	int intCha;
	int intMana;
	int intMaxMana;
	int intAC;
	int intExPoints;
	int intHunger;
	int intAlign;
};

#endif