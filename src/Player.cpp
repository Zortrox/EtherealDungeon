#include "Player.h"
#include <math.h>

using namespace std;

Player::Player()
{
	bLanternOut = false;
	oilLevel = 81;
	bHasLantern = true;

	intGold = 20;

	strRank = "Awesome";

	//base stats
	intStr = 5;
	intDex = 5;
	intCon = 5;
	intInt = 5;
	intWis = 5;
	intCha = 5;

	intLevel = 1;
	intMaxHP = 2;
	intHP = intMaxHP;
	intMaxMana = 2;
	intMana = intMaxMana;
	intAC = 10;
	intExPoints = 0;

	etherealTurns = 0;
	maxEtherealTurns = 0;

	intHunger = 500;
	intAlign = 0;
}
Player::~Player()
{

}

bool Player::canMove(int x, int y, vector<vector<Tile>> &vec_TempTiles)
{
	if (vec_TempTiles.at(y).at(x).getWalkable())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::setPlayerLevels(unsigned long long lngTurns)
{
	//heal player over time
	double conTurn = (int)(5 / pow((double)intCon/10, 2));
	if (conTurn == 0){conTurn = 1;}
	int healTurn = lngTurns%(int)conTurn;
	if (healTurn == 0 && intHP != intMaxHP)
	{
		setHP(intHP + 1);
		if (intHP > intMaxHP)
		{
			setHP(intMaxHP);
		}
	}

	//give mana back over time
	double intTurn = (int)(5 / pow((double)intInt/10, 2));
	if (intTurn == 0){intTurn = 1;}
	int manaTurn = lngTurns%(int)intTurn;
	if (manaTurn == 0 && intMana != intMaxMana)
	{
		setMana(intMana+intMaxMana/5);
		if (intMana > intMaxMana)
		{
			setMana(intMaxMana);
		}
	}

	//give ethereal turns back over time
	double wisTurn = (int)(20 / pow((double)intWis/10, 2));
	if (wisTurn == 0){wisTurn = 1;}
	int eTurn = lngTurns%(int)wisTurn;
	if (eTurn == 0 && getETurns() != getMaxETurns())
	{
		setETurns(getETurns()+getMaxETurns()/5);
		if (etherealTurns > maxEtherealTurns)
		{
			setETurns(maxEtherealTurns);
		}
	}

	//drain oil if lantern is out
	int oilTurn = lngTurns%50;
	if (oilTurn == 0)
	{
		if (oilLevel > 0 && bLanternOut == true)
		{
			oilLevel -= 1;
		}
		else
		{
			bLanternOut = false;
		}
	}
}

int Player::lanternSight()
{
	int sight = 3;
	if (bLanternOut)
	{
		if (oilLevel >= 10)
		{
			sight = 17;
		}
		else
		{
			sight = oilLevel + 7;
		}
	}

	return sight;
}
void Player::lanternState()
{
	if (bLanternOut)
	{
		bLanternOut = false;
	}
	else
	{
		bLanternOut = true;
	}
	
}
bool Player::hasLantern()
{
	return bHasLantern;
}
bool Player::lanternOut()
{
	return bLanternOut;
}

//getters and setters
std::string Player::getRank()
{
	return strRank;
}
int Player::getStr()
{
	return intStr;
}
int Player::getDex()
{
	return intDex;
}
int Player::getCon()
{
	return intCon;
}
int Player::getInt()
{
	return intInt;
}
int Player::getWis()
{
	return intWis;
}
int Player::getCha()
{
	return intCha;
}
int Player::getMana()
{
	return intMana;
}
int Player::getMaxMana()
{
	return intMaxMana;
}
int Player::getAC()
{
	return intAC;
}
int Player::getExPoints()
{
	return intExPoints;
}
int Player::getAlign()
{
	return intAlign;
}
int Player::getHunger()
{
	return intHunger;
}

void Player::setRank(std::string Rank)
{
	strRank = Rank;
}
void Player::setStr(int Str)
{
	intStr = Str;
}
void Player::setDex(int Dex)
{
	intDex = Dex;
}
void Player::setCon(int Con)
{
	intCon = Con;
}
void Player::setInt(int Int)
{
	intInt = Int;
}
void Player::setWis(int Wis)
{
	intWis = Wis;
}
void Player::setCha(int Cha)
{
	intCha = Cha;
}
void Player::setMana(int Mana)
{
	intMana = Mana;
}
void Player::setMaxMana(int MaxMana)
{
	intMaxMana = MaxMana;
}
void Player::setAC(int AC)
{
	intAC = AC;
}
void Player::setExPoints(int ExPoints)
{
	intExPoints = ExPoints;
	
	if (intExPoints >= 100000000 && getLevel() < 30) {intLevel++;}
	else if (intExPoints >= 90000000 && getLevel() < 29) {intLevel++;}
	else if (intExPoints >= 80000000 && getLevel() < 28) {intLevel++;}
	else if (intExPoints >= 70000000 && getLevel() < 27) {intLevel++;}
	else if (intExPoints >= 60000000 && getLevel() < 26) {intLevel++;}
	else if (intExPoints >= 50000000 && getLevel() < 25) {intLevel++;}
	else if (intExPoints >= 40000000 && getLevel() < 24) {intLevel++;}
	else if (intExPoints >= 30000000 && getLevel() < 23) {intLevel++;}
	else if (intExPoints >= 20000000 && getLevel() < 22) {intLevel++;}
	else if (intExPoints >= 10000000 && getLevel() < 21) {intLevel++;}
	else if (intExPoints >= 5120000 && getLevel() < 20) {intLevel++;}
	else if (intExPoints >= 2560000 && getLevel() < 19) {intLevel++;}
	else if (intExPoints >= 1280000 && getLevel() < 18) {intLevel++;}
	else if (intExPoints >= 640000 && getLevel() < 17) {intLevel++;}
	else if (intExPoints >= 320000 && getLevel() < 16) {intLevel++;}
	else if (intExPoints >= 160000 && getLevel() < 15) {intLevel++;}
	else if (intExPoints >= 80000 && getLevel() < 14) {intLevel++;}
	else if (intExPoints >= 40000 && getLevel() < 13) {intLevel++;}
	else if (intExPoints >= 20000 && getLevel() < 12) {intLevel++;}
	else if (intExPoints >= 10000 && getLevel() < 11) {intLevel++;}
	else if (intExPoints >= 5120 && getLevel() < 10) {intLevel++;}
	else if (intExPoints >= 2560 && getLevel() < 9) {intLevel++;}
	else if (intExPoints >= 1280 && getLevel() < 8) {intLevel++;}
	else if (intExPoints >= 640 && getLevel() < 7) {intLevel++;}
	else if (intExPoints >= 320 && getLevel() < 6) {intLevel++;}
	else if (intExPoints >= 160 && getLevel() < 5) {intLevel++;}
	else if (intExPoints >= 80 && getLevel() < 4) {intLevel++;}
	else if (intExPoints >= 40 && getLevel() < 3) {intLevel++;}
	else if (intExPoints >= 20 && getLevel() < 2) {intLevel++;}
}
void Player::setHunger(int Hunger)
{
	intHunger = Hunger;
}
void Player::setAlign(int Align)
{
	intAlign = Align;
}

int Player::getOil()
{
	return oilLevel;
}
void Player::setOil(int oil)
{
	oilLevel = oil;
	if (oilLevel > 160)
	{
		oilLevel = 160;
	}
}

int Player::getGold()
{
	return intGold;
}
void Player::setGold(int gold)
{
	intGold = gold;
}

int Player::getETurns()
{
	return etherealTurns;
}
void Player::setETurns(int turns)
{
	etherealTurns = turns;
}
int Player::getMaxETurns()
{
	return maxEtherealTurns;
}
void Player::setMaxETurns(int turns)
{
	maxEtherealTurns = turns;
}