#include <vector>
#include <string>
#include <iostream>
#include <curses.h>
#include "Player.h"
#include "Game.h"

using namespace std;

int main()
{
	bool again = true;
	do
	{
		Game currentGame;

		again = currentGame.playAgain();
	}
	while(again);

	return 0;
}