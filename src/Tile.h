#pragma once

#ifndef _Tile_included_
#define _Tile_included_

#include <vector>
#include "Item.h"
#include "Creature.h"

class Tile{
public:
	Tile();
	virtual ~Tile();

	//getters & setters
	void setWalkable(bool walk);
	bool getWalkable();

	void setVisible(bool vis);
	bool getVisible();

	void setUpstairs(bool up);
	bool getUpstairs();

	void setDownstairs(bool down);
	bool getDownstairs();

	void setSeen(bool seen);
	bool getSeen();

	std::vector<Item*> getTileItemsVector();
	void setTileItemsVector(std::vector<Item*> iVec);
	Creature* getTileCreature();
	void setTileCreature(Creature* creature);
protected:

private:
	bool walkable;
	bool visible;
	bool upstairs;
	bool downstairs;
	bool beenSeen;
	std::vector<Item*> vec_TileItems;
	Creature* tileCreature;
};

#endif