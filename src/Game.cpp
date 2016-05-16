#include "Game.h"
#include "parser.h"
#include <sstream>
#include <algorithm>

using namespace std;

//TODO: Change README file
//TODO: Balancing of attack and stats
//TODO: Add character equipment
//TODO: Add magic
//TODO: Add max amount of items on tile/in backpack

Game::Game()
{
	curWin = initscr();		//start screen module
	noecho();				//don't output keyboard commands
	start_color();			//start color module
	curs_set(0);			//don't blink cursor
	keypad(curWin, TRUE);	//enable arrow keys
	resize_term(27, 100);	//resize window buffer

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);		//oil flask color
	init_pair(7, COLOR_BLUE, COLOR_BLACK);

	//colors for stats
	init_pair(11, COLOR_WHITE, COLOR_RED);
	init_pair(12, COLOR_WHITE, COLOR_GREEN);
	init_pair(13, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(14, COLOR_WHITE, COLOR_BLUE);
	init_pair(15, COLOR_WHITE, COLOR_YELLOW);
	init_pair(16, COLOR_WHITE, COLOR_CYAN);

	msgSelectionColor = COLOR_PAIR(6) | A_REVERSE;

	//display start screen
	startScreen();

	if (gameOver == false)
	{
		//create new character
		playerLevel = player.getLevel();
		characterLevelUp("new", 10);

		//messages
		oldMessageSize = 0;
		newUpdate = false;
		intCurrentMessageLine = 0;

		//pathing
		PathFound = false;

		//vision
		vec_CharTiles.resize(20);
		for (size_t i = 0; i < vec_CharTiles.size(); i++)
		{
			vec_CharTiles.at(i).resize(79);
		}

		init_Level(); //create first level

		//start turn loop
		do
		{
			takeTurn();
		}
		while (gameOver == false);

		//display score
		clear();
		score = player.getExPoints();
		score += player.getInventory().size();
		stringstream strScore;
		strScore << score;
		if (player.getHP() <= 0)
		{
			outputText("You have died.", 0, 3);
		}
		else
		{
			outputText("You have escaped the dungeon.", 0, 3);
		}
		outputText("Score: " + strScore.str(), 0, 4);
		outputText("The game has ended. Press r to play again. Press q to quit.", 0, 6);
		do
		{
			char_Button = wgetch(curWin);

			switch(char_Button)
			{
				case 'r':
				{
					restart = true;
					break;
				}
				case 'q':
				{
					restart = false;
					break;
				}
				case 3: //KEY_UP
				{
					if (intCurrentMessageLine >= 0 && !vec_Messages.empty())
					{
						intCurrentMessageLine--;
						drawMessages();
					}
					break;
				}
				case 2: //KEY_DOWN
				{
					if (intCurrentMessageLine < (signed)vec_Messages.size() - 1)
					{
						intCurrentMessageLine++;
						drawMessages();
					}
					break;
				}
			}
		}
		while (char_Button != 'r' && char_Button != 'q');

		for (size_t i = 0; i < vec_Levels.size(); i++)
		{
			delete vec_Levels.at(i);
		}
	}
}
Game::~Game()
{
	endwin();
}
int Game::popupMessage(string strMessage, vector<string> vec_ChoiceNames, int defaultSelection, bool bTextbox, string &strResponse, int maxTextLength)
{
	int maxLength = 0;
	vector<string> substrMessages;
	string tempMessage = strMessage;
	int currentSelection = defaultSelection;
	char char_Command = 0;
	int intBoxTop = 7;
	int intBoxCenter = 50;
	while (tempMessage.find("\n") != -1)
	{
		int len = tempMessage.find("\n");
		substrMessages.push_back(tempMessage.substr(0, len));
		tempMessage = tempMessage.substr(len+1, tempMessage.length()-1);
		if ((signed)substrMessages.back().length() > maxLength)
		{
			maxLength = substrMessages.back().length();
		}
		
	}
	if (substrMessages.empty())
	{
		substrMessages.push_back(strMessage);
		maxLength = strMessage.length();
	}
	else
	{
		substrMessages.push_back(tempMessage);
		if ((signed)substrMessages.back().length() > maxLength)
		{
			maxLength = substrMessages.back().length();
		}
	}

	//create box
	int boxRadius = (int)((maxLength/2)+2);
	if (boxRadius < 8){boxRadius = 8;}
	for (int i = intBoxCenter - boxRadius; i <= intBoxCenter + boxRadius; i++)
	{
		chtype boxAttr = COLOR_PAIR(6);
		attron(boxAttr);
		//clear out box area
		for (size_t m = intBoxTop-1; m < substrMessages.size() + 7 + intBoxTop + 2; m++)
		{
			mvaddch(m, i, ' ');
			if (i == intBoxCenter - boxRadius)
			{
				mvaddch(m, i-1, ' ');
			}
			else if (i == intBoxCenter + boxRadius)
			{
				mvaddch(m, i+1, ' ');
			}
		}
		mvaddch(intBoxTop, i, '-');
		if (i == intBoxCenter - boxRadius || i == intBoxCenter + boxRadius)
		{
			mvaddch(1+intBoxTop, i, '|');
			for (size_t k = 0; k < substrMessages.size(); k++)
			{
				attroff(boxAttr);
				outputText(substrMessages.at(k), (int)intBoxCenter - (substrMessages.at(k).length()/2), k + 2 + intBoxTop);
				attron(boxAttr);
				mvaddch(k+2+intBoxTop, i, '|');
			}
			mvaddch(substrMessages.size() + 1 + intBoxTop, i, '|');
			mvaddch(substrMessages.size() + 2 + intBoxTop, i, '|');
			mvaddch(substrMessages.size() + 3 + intBoxTop, i, '|');
			mvaddch(substrMessages.size() + 4 + intBoxTop, i, '|');
			mvaddch(substrMessages.size() + 5 + intBoxTop, i, '|');
			mvaddch(substrMessages.size() + 6 + intBoxTop, i, '|');
		}
		mvaddch(substrMessages.size() + 7 + intBoxTop, i, '-');
		attroff(boxAttr);
	}

	do
	{
		if (bTextbox == true)
		{
			int startingX = intBoxCenter-(maxTextLength/2);
			attron(COLOR_PAIR(1) | A_REVERSE);
			outputText(string(maxTextLength, ' '), startingX, substrMessages.size() + 5 + intBoxTop);
			outputText(strResponse, startingX, substrMessages.size() + 5 + intBoxTop);
			attroff(COLOR_PAIR(1) | A_REVERSE);
			if (maxTextLength > (signed)strResponse.length())
			{
				attron(msgSelectionColor);
				outputText(" ", startingX + strResponse.length(), substrMessages.size() + 5 + intBoxTop);
				attroff(msgSelectionColor);
			}
		}
		else
		{
			for (size_t i = 0; i < vec_ChoiceNames.size(); i++)
			{
				if (currentSelection == i){attron(msgSelectionColor);}
				outputText(" " + vec_ChoiceNames.at(i) + " ",
					(intBoxCenter-boxRadius) + ((boxRadius*2)/(vec_ChoiceNames.size()+1))*(i+1) - (vec_ChoiceNames.at(i).length()/2),
					substrMessages.size() + 5 + intBoxTop);
				attroff(msgSelectionColor);
			}
		}

		refresh();
		char_Command = wgetch(curWin);

		if (((char_Command >= 'A' && char_Command <= 'Z') || (char_Command >= 'a' && char_Command <= 'z')
			|| char_Command == ' ' || char_Command == '\'') && (signed)strResponse.length() < maxTextLength && bTextbox == true)
		{
			strResponse += string(1, char_Command);
		}
		else if (bTextbox == true && (char_Command == 8 || char_Command == 4) && strResponse.length() > 0)
		{
			strResponse = strResponse.substr(0, strResponse.size()-1);
		}
		else if (char_Command == 4 && currentSelection > 0 && bTextbox == false)
		{
			currentSelection--;
		}
		else if (char_Command == 5 && currentSelection < (signed)vec_ChoiceNames.size() - 1 && bTextbox == false)
		{
			currentSelection++;
		}
		else if (char_Command == '\n')
		{
			return currentSelection;
		}
	}
	while (char_Command != '\n');

	return 0;
}
void Game::startScreen()
{
	int selectedOption = -1;
	int currentOption = 0;
	vector<string> vec_Options;
	vec_Options.push_back("New");
	vec_Options.push_back("Load");
	vec_Options.push_back("Quit");

	while (selectedOption == -1)
	{
		clear();
		outputText(" ____| |   |                         |   ____|          |                     ", 3, 2);
		outputText(" __|   __| __ \\   _ \\  __| _ \\  _` | |   |    _ \\   __| __|  __| _ \\  __|  __|", 3, 3);
		outputText(" |     |   | | |  __/ |    __/ (   | |   __| (   | |    |   |    __/\\__ \\__ \\", 3, 4);
		outputText("_____|\\__|_| |_|\\___|_|  \\___|\\__,_|_|  _|  \\___/ _|   \\__|_|  \\___|____/____/", 3, 5);

		for (size_t i = 0; i < vec_Options.size(); i++)
		{
			if (i == currentOption){attron(msgSelectionColor);}
			outputText(" " + vec_Options.at(i) + " ", 10, 13+(2*i));
			attroff(msgSelectionColor);
		}
		refresh();

		char_Button = wgetch(curWin);

		switch(char_Button)
		{
			case 'w':
			case 3: //KEY_UP
			{
				if (currentOption > 0)
				{
					currentOption--;
				}
				break;
			}
			case 's':
			case 2:	//KEY_DOWN
			{
				if (currentOption < (signed)vec_Options.size() - 1)
				{
					currentOption++;
				}
				break;
			}
			case ' ':
			case '\n':
			{
				selectedOption = currentOption;
				if (vec_Options.at(currentOption) == "New")
				{
					//start game
					gameOver = false;
					etherealMode = false;
					restart = true;
					char_Button = '>';
					intCurrentLevel = 1;
					lngTurns = 0;
					score = 0;
				}
				else if (vec_Options.at(currentOption) == "Quit")
				{
					//quit game
					gameOver = true;
					restart = false;
				}
				else
				{
					selectedOption = -1;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
void Game::characterLevelUp(string characterType, int skillPoints)
{
	bool foundName = false;
	string tempName = "";
	char char_Command = 0;

	//FIND NAME
	while (foundName == false && characterType == "new")
	{
		clear();

		vec_Options.clear();
		popupMessage("What is your adventurer's name?",vec_Options, 0, true, tempName, 15);

		int intChoice;
		vec_Options.clear();
		vec_Options.push_back("Yes");
		vec_Options.push_back("No");
		intChoice = popupMessage("Are you sure you want\n" + tempName + "\nto be your character's name?",
			vec_Options, 1, false, strNOMESSAGE, 0);
		if (intChoice == 0)
		{
			foundName = true;
			player.setName(tempName);
		}
	}

	bool bDone = false;
	int currentSelection = 0;
	string currentName = player.getName();
	vector<int> newStatNums;

	int currentLevel = player.getLevel();
	int currentCon = player.getCon();
	newStatNums.push_back(0);
	int currentWis = player.getWis();
	newStatNums.push_back(0);
	int currentDex = player.getDex();
	newStatNums.push_back(0);
	int currentInt = player.getInt();
	newStatNums.push_back(0);
	int currentStr = player.getStr();
	newStatNums.push_back(0);
	int currentCha = player.getCha();
	newStatNums.push_back(0);

	while (bDone == false)
	{
		clear();

		outputText(currentName, 10, 3);

		outputText("Level: " + to_string(static_cast<long long>(currentLevel)), 3, 1);
		outputText("Name:", 4, 3);

		for (int i = 0; i < 6; i++)
		{
			if (currentSelection == i){attron(COLOR_PAIR(6));}
			else {attron(COLOR_PAIR(1));}
			outputText(string(newStatNums.at(i), '#'), 46, 2+4*i);
			outputText(string(newStatNums.at(i), '#'), 46, 3+4*i);
			outputText(string(newStatNums.at(i), '#'), 46, 4+4*i);
			mvaddch(2+4*i, 45, '|');
			mvaddch(3+4*i, 45, '|');
			mvaddch(4+4*i, 45, '|');
			attroff(COLOR_PAIR(6));

			mvaddch(3+(4*i), 39, '+');
			outputText(string(68, '-'), 28, 1+(4*i));
			mvaddch(2+4*i, 28, '|');
			mvaddch(3+4*i, 28, '|');
			mvaddch(4+4*i, 28, '|');
			outputText(string(68, '-'), 28, 5+(4*i));
		}

		//draw other 6 stats
		outputText("Con: " + to_string(static_cast<long long>(currentCon)), 30, 3);
		outputText(to_string(static_cast<long long>(newStatNums.at(0))), 41, 3);
		outputText("Wis: " + to_string(static_cast<long long>(currentWis)), 30, 7);
		outputText(to_string(static_cast<long long>(newStatNums.at(1))), 41, 7);
		outputText("Dex: " + to_string(static_cast<long long>(currentDex)), 30, 11);
		outputText(to_string(static_cast<long long>(newStatNums.at(2))), 41, 11);
		outputText("Int: " + to_string(static_cast<long long>(currentInt)), 30, 15);
		outputText(to_string(static_cast<long long>(newStatNums.at(3))), 41, 15);
		outputText("Str: " + to_string(static_cast<long long>(currentStr)), 30, 19);
		outputText(to_string(static_cast<long long>(newStatNums.at(4))), 41, 19);
		outputText("Cha: " + to_string(static_cast<long long>(currentCha)), 30, 23);
		outputText(to_string(static_cast<long long>(newStatNums.at(5))), 41, 23);

		//Skill Points
		outputText("SKILL POINTS LEFT", 6, 9);
		outputText("------", 11, 11);
		outputText("------", 11, 15);
		mvaddch(12, 11, '|');mvaddch(12, 16, '|');
		mvaddch(13, 11, '|');mvaddch(13, 16, '|');
		mvaddch(14, 11, '|');mvaddch(14, 16, '|');
		outputText(to_string(static_cast<long long>(skillPoints)), 13, 13);

		//DONE
		if (currentSelection == 6){attron(msgSelectionColor);}
		else {attron(COLOR_PAIR(1) | A_REVERSE);}
		outputText(" DONE ", 11, 25);
		attroff(msgSelectionColor);

		refresh();

		char char_Command = wgetch(curWin);

		if ((char_Command == 3 || char_Command == 'w') && currentSelection > 0)	//KEY_UP
		{
			currentSelection--;
		}
		else if ((char_Command == 2 || char_Command == 's') && currentSelection < 6)	//KEY_DOWN
		{
			currentSelection++;
		}
		else if (char_Command == '\n' && currentSelection == 6)
		{
			int intChoice;
			vec_Options.clear();
			vec_Options.push_back("Yes");
			vec_Options.push_back("No");
			if (skillPoints > 1)
			{
				intChoice = popupMessage("You have " + to_string((long long)skillPoints) + " skill points remaining.\n"
					"Are you sure you want to exit without using them?",vec_Options, 1, false, strNOMESSAGE, 0);
			}
			else if (skillPoints == 1)
			{
				intChoice = popupMessage("You have " + to_string((long long)skillPoints) + " skill point remaining.\n"
					"Are you sure you want to exit without using it?",vec_Options, 1, false, strNOMESSAGE, 0);
			}
			else
			{
				intChoice = popupMessage("Are you sure you want these stats?",
					vec_Options, 1, false, strNOMESSAGE, 0);
			}
			if (intChoice == 0)
			{
				bDone = true;
			}
		}
		//CHANGE MAIN STATS
		else if ((char_Command == 4 || char_Command == 'a') && currentSelection < 6)	//KEY_LEFT
		{
			if (newStatNums.at(currentSelection) > 0)
			{
				newStatNums.at(currentSelection)--;
				skillPoints++;
			}
		}
		else if ((char_Command == 5 || char_Command == 'd') && currentSelection < 6)		//KEY_RIGHT
		{
			if (skillPoints > 0)
			{
				newStatNums.at(currentSelection)++;
				skillPoints--;
			}
		}
	}

	//SET STATS
	player.setCon(player.getCon()+newStatNums.at(0));
	player.setWis(player.getWis()+newStatNums.at(1));
	player.setDex(player.getDex()+newStatNums.at(2));
	player.setInt(player.getInt()+newStatNums.at(3));
	player.setStr(player.getStr()+newStatNums.at(4));
	player.setCha(player.getCha()+newStatNums.at(5));

	player.setMaxHP(player.getMaxHP()+((int)(player.getCon()/5))*(mt()%8+1));			//SET HEALTH
	player.setHP(player.getMaxHP());

	player.setMaxMana(player.getMaxMana()+((int)player.getInt()/5)*(mt()%8+1));			//SET MANA
	player.setMana(player.getMaxMana());

	player.setMaxETurns(player.getMaxETurns() + ((int)player.getWis()/5)*(mt()%3+1));										//SET ETHEREAL TURNS
	player.setETurns(player.getMaxETurns());
}
bool Game::playAgain()
{
	return restart;
}
void Game::outputText(string str_Message, int beginX, int beginY)
{
	move(beginY, beginX);
	addstr(str_Message.c_str());
}
string Game::itemArticleName(Item* &tempItem)
{
	if (tolower(tempItem->getName().at(0)) == 'a' ||
		tolower(tempItem->getName().at(0)) == 'e' ||
		tolower(tempItem->getName().at(0)) == 'i' ||
		tolower(tempItem->getName().at(0)) == 'o' ||
		tolower(tempItem->getName().at(0)) == 'u')
	{
		return "an";
	}
	else if (tempItem->getName() == "gold" || tempItem->getName() == "chainmail")
	{
		return "some";
	}
	else
	{
		return "a";
	}
}
void Game::createNewLevel()
{
	//add new level to level vector
	vec_Levels.push_back(new DungeonLevel);
	
	reset_Level();

	//set tiles that player can walk on
	for(int x = 0; x < vec_Levels.at(intCurrentLevel-1)->getWidth(); x++)
	{
		for(int y = 0; y < vec_Levels.at(intCurrentLevel-1)->getHeight(); y++)
		{
			if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '.' ||
				vec_Levels.at(intCurrentLevel-1)->at(x,y) == '#')
			{
				vec_Tiles.at(y).at(x).setWalkable(true);
			}
			else if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '<')
			{
				vec_Tiles.at(y).at(x).setWalkable(true);
				vec_Tiles.at(y).at(x).setUpstairs(true);
			}
			else if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '>')
			{
				vec_Tiles.at(y).at(x).setWalkable(true);
				vec_Tiles.at(y).at(x).setDownstairs(true);
			}
		}
	}

	//seed level with items and monsters
	for (int i = 0; i < (signed)(mt()%8)+4; i++)
	{
		bool bPlaced = false;
		while (!bPlaced)
		{
			int x = mt()%79;
			int y = mt()%20;

			if (vec_Tiles.at(y).at(x).getWalkable() == true && vec_Tiles.at(y).at(x).getUpstairs() == false && vec_Tiles.at(y).at(x).getDownstairs() == false)
			{
				Item* tempItem = iFac.generateItem(intCurrentLevel*2);
				vector<Item*> tempVec = vec_Tiles.at(y).at(x).getTileItemsVector();
				tempVec.push_back(tempItem);
				vec_Tiles.at(y).at(x).setTileItemsVector(tempVec);
				bPlaced = true;
			}
		}
	}
	for (int i = 0; i < (signed)(mt()%10)+4; i++)
	{
		bool bPlaced = false;
		while (!bPlaced)
		{
			int x = mt()%79;
			int y = mt()%20;

			if (vec_Tiles.at(y).at(x).getTileCreature() == NULL &&
				vec_Tiles.at(y).at(x).getWalkable() == true
				&& vec_Tiles.at(y).at(x).getUpstairs() == false && vec_Tiles.at(y).at(x).getDownstairs() == false)
			{
				//TODO: Add creature item vector for drops
				Creature* tempCreature = cFac.generateCreature(intCurrentLevel);
				tempCreature->setXPos(x);
				tempCreature->setYPos(y);
				vec_Tiles.at(y).at(x).setWalkable(false);
				tempCreature->setHP(tempCreature->getMaxHP());
				vec_Tiles.at(y).at(x).setTileCreature(tempCreature);
				bPlaced = true;
			}
		}
	}
}
void Game::init_Level()
{
	//create new level if not in the vector
	if ((signed)vec_Levels.size() < intCurrentLevel)
	{
		createNewLevel();
	}
	else
	{
		reset_Level();
	}

	//set player to starting point
	int tempX;
	int tempY;
	for(int x = 0; x < vec_Levels.at(intCurrentLevel-1)->getWidth(); x++)
	{
		for(int y = 0; y < vec_Levels.at(intCurrentLevel-1)->getHeight(); y++)
		{
			if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '<' && char_Button == '>')
			{
				tempX = x;
				tempY = y;
			}
			if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '>' && char_Button == '<')
			{
				tempX = x;
				tempY = y;
			}
		}
	}
	player.setXPos(tempX);
	player.setYPos(tempY);

	//draw level for first time
	redrawScreen();
}
void Game::reset_Level()
{
	clear();
	vec_Tiles = vec_Levels.at(intCurrentLevel-1)->getTileVector();
	strLevelName = "Dlvl:" + to_string(static_cast<long long>(intCurrentLevel));
}
void Game::changeLevel(int changeAmount)
{
	vec_Levels.at(intCurrentLevel-1)->setTileVector(vec_Tiles);
	intCurrentLevel += changeAmount;
	init_Level();
}
void Game::redrawScreen()
{
	move(2,0);
	clrtobot();

	//set tile visible status (vision)
	setTilesVisible(vec_CharTiles, player.getXPos(), player.getYPos(), -1, player.lanternSight());
	setTilesInvisible(vec_CharTiles);

	drawDungeon();
	drawItems();
	drawCreatures();
	drawPlayer();
	drawMessages();
	drawStats();

	refresh();
}
void Game::drawStats()
{
	attron(A_REVERSE);

	//clear stats area with blankspace
	for (int i = 0; i < 27; i++)
	{
		if (i < 23)
		{
			outputText(string(20, ' '), 80, i);
		}
		else
		{
			outputText(string(100, ' '), 0, i);
		}
	}

	//display player stats

	string strHunger;
	if (player.getHunger() > 999 && player.getHunger() < 2000){strHunger = "Satiated";}
	else if (player.getHunger() > 149 && player.getHunger() < 1000){strHunger = "Not hungry";}
	else if (player.getHunger() > 49 && player.getHunger() < 150){strHunger = "Hungry";}
	else if (player.getHunger() > -1 && player.getHunger() < 50){strHunger = "Weak";}
	else if (player.getHunger() < 0){strHunger = "Fainting";}

	string strAlignment;
	if (player.getAlign() > -5 && player.getAlign() < 5){strAlignment = "Neutral";}
	else if (player.getAlign() > 4){strAlignment = "Lawful";}
	else if (player.getAlign() < -4){strAlignment = "Chaotic";}

	outputText(player.getName() + " the " + player.getRank(), 0, 23);

	outputText("HP:" + to_string(static_cast<long long>(player.getHP())) + "(" + to_string(static_cast<long long>(player.getMaxHP())) + ")", 0, 24);
	outputText("Ma:" + to_string(static_cast<long long>(player.getMana())) + "(" + to_string(static_cast<long long>(player.getMaxMana())) + ")", 24, 24);
	outputText("AC:" + to_string(static_cast<long long>(player.getAC())), 40, 24);
	if (player.getLevel() < 18)
	{
		outputText("Exp:" + to_string(static_cast<long long>(player.getLevel())) + "/" + to_string(static_cast<long long>(player.getExPoints())), 47, 24);
	}
	else
	{
		outputText("Exp:" + to_string(static_cast<long long>(player.getLevel())), 47, 24);
	}
	attron(COLOR_PAIR(15) | A_BOLD);
	outputText("Gold:" + to_string(static_cast<long long>(player.getGold())), 63, 24);
	attroff(COLOR_PAIR(15) | A_BOLD);

	attron(COLOR_PAIR(15) | A_BOLD);
	outputText("Con:" + to_string(static_cast<long long>(player.getCon())), 0, 25);
	attroff(COLOR_PAIR(15) | A_BOLD);
	attron(COLOR_PAIR(14) | A_BOLD);
	outputText("Wis:" + to_string(static_cast<long long>(player.getWis())), 8, 25);
	attroff(COLOR_PAIR(14) | A_BOLD);
	attron(COLOR_PAIR(12));
	outputText("Dex:" + to_string(static_cast<long long>(player.getDex())), 16, 25);
	attroff(COLOR_PAIR(12));
	attron(COLOR_PAIR(13));
	outputText("Int:" + to_string(static_cast<long long>(player.getInt())), 24, 25);
	attroff(COLOR_PAIR(13));
	attron(COLOR_PAIR(11));
	outputText("Str:" + to_string(static_cast<long long>(player.getStr())), 32, 25);
	attroff(COLOR_PAIR(11));
	attron(COLOR_PAIR(16));
	outputText("Cha:" + to_string(static_cast<long long>(player.getCha())), 40, 25);
	attroff(COLOR_PAIR(16));
	outputText(strAlignment, 63, 25);

	outputText(strLevelName, 0, 26);
	outputText(strHunger, 24, 26);
	outputText("T:" + to_string(static_cast<long long>(lngTurns)), 40, 26);
	outputText("ET:" + to_string(static_cast<long long>(player.getETurns())) + "(" + to_string(static_cast<long long>(player.getMaxETurns())) + ")", 63, 26);

	//Draw player equipped items


	stringstream lanternDraw;
	int tempOil = player.getOil();

	outputText(string(18, '-'), 81, 20);

	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			lanternDraw << "*----*";
		}
		else if (i == 5)
		{
			lanternDraw << ".----.";
		}
		else
		{
			if (tempOil >= 40*i)
			{
				lanternDraw << "|====|";
			}
			else if (tempOil >= 40*i-20)
			{
				lanternDraw << "|____|";
			}
			else
			{
				lanternDraw << "|    |";
			}

			if (i == 2)
			{
				if (player.lanternOut())
				{
					lanternDraw << " ON/off";
				}
				else
				{
					lanternDraw << " on/OFF";
				}
			}
			else if (i == 3)
			{
				lanternDraw << " Lantern";
			}
		}
		outputText(lanternDraw.str(), 82, 26-i);
		lanternDraw.str(strNOMESSAGE);
	}

	//draw equipment separator line
	for (int i = 0; i < 27; i++)
	{
		outputText(string(1, '|'), 80, i);
	}

	attroff(A_REVERSE);
}
void Game::drawMessages()
{
	//clear the message lines
	outputText(string(79, ' '), 0, 0);
	outputText(string(79, ' '), 0, 1);

	if (newUpdate)
	{
		outputText(str_Update, 0, 0);
		newUpdate = false;
	}
	else if ((signed)vec_Messages.size() > oldMessageSize)
	{
		intCurrentMessageLine = vec_Messages.size();

		if (vec_Messages.size() - oldMessageSize > 1)
		{
			outputText(vec_Messages.at(intCurrentMessageLine - 2), 0, 0);
			outputText(vec_Messages.at(intCurrentMessageLine - 1), 0, 1);
			oldMessageSize = vec_Messages.size() - 1;
		}
		else
		{
			outputText(vec_Messages.at(intCurrentMessageLine - 1), 0, 0);
			oldMessageSize = vec_Messages.size();
		}
	}
	else if ((signed)vec_Messages.size() > intCurrentMessageLine && (char_Button == 3 || char_Button == 2)) //and if key_up/key_down were pressed
	{
		if (intCurrentMessageLine == -1)
		{
			outputText(" -- TOP -- ", 0, 0);
			outputText(vec_Messages.at(intCurrentMessageLine + 1), 0, 1);
		}
		else if (intCurrentMessageLine == vec_Messages.size() - 1)
		{
			outputText(vec_Messages.at(intCurrentMessageLine), 0, 0);
			outputText(" -- BOTTOM -- ", 0, 1);
		}
		else
		{
			outputText(vec_Messages.at(intCurrentMessageLine), 0, 0);
			outputText(vec_Messages.at(intCurrentMessageLine + 1), 0, 1);
		}
	}
}
void Game::drawPlayer()
{
	//display player
	move(player.getYPos()+2, player.getXPos());
	chtype playerColor;
	if (etherealMode == true) {playerColor = COLOR_PAIR(2);}
	else {playerColor = COLOR_PAIR(2);}
	attron(playerColor);
	addch('@');
	attroff(playerColor);
}
void Game::drawCreatures()
{
	for(int x = 0; x < vec_Levels.at(intCurrentLevel-1)->getWidth(); x++)
	{
		for(int y = 0; y < vec_Levels.at(intCurrentLevel-1)->getHeight(); y++)
		{
			if (vec_Tiles.at(y).at(x).getTileCreature() != NULL &&vec_Tiles.at(y).at(x).getVisible())
			{
				move(y+2,x);
				chtype monsterColor;
				if (etherealMode == true) {monsterColor = COLOR_PAIR(5) | A_BOLD;}
				else {monsterColor = COLOR_PAIR(3);}
				attron(monsterColor);
				addch(vec_Tiles.at(y).at(x).getTileCreature()->getDisplayChar());
				attroff(monsterColor);
			}
		}
	}
}
void Game::drawItems()
{
	for(int x = 0; x < vec_Levels.at(intCurrentLevel-1)->getWidth(); x++)
	{
		for(int y = 0; y < vec_Levels.at(intCurrentLevel-1)->getHeight(); y++)
		{
			if (!vec_Tiles.at(y).at(x).getTileItemsVector().empty() && vec_Tiles.at(y).at(x).getVisible())
			{
				move(y+2,x);
				chtype itemColor;
				chtype oilColor;
				chtype goldColor;
				if (etherealMode == true) {itemColor = COLOR_PAIR(6) | A_DIM; oilColor = COLOR_PAIR(6); goldColor = COLOR_PAIR(6) | A_BOLD;}
				else {itemColor = COLOR_PAIR(4) | A_DIM; oilColor = COLOR_PAIR(6); goldColor = COLOR_PAIR(4) | A_BOLD;}
				if (vec_Tiles.at(y).at(x).getTileItemsVector().at(0)->getName().find("oil flask") != -1)
				{
					attron(oilColor);
					addch(vec_Tiles.at(y).at(x).getTileItemsVector().at(0)->getDisplayChar());
					attroff(oilColor);
				}
				else if (vec_Tiles.at(y).at(x).getTileItemsVector().at(0)->getName() == "gold")
				{
					attron(goldColor);
					addch(vec_Tiles.at(y).at(x).getTileItemsVector().at(0)->getDisplayChar());
					attroff(goldColor);
				}
				else
				{
					attron(itemColor);
					addch(vec_Tiles.at(y).at(x).getTileItemsVector().at(0)->getDisplayChar());
					attroff(itemColor);
				}
			}
		}
	}
}
void Game::drawDungeon()
{
	for(int x = 0; x < vec_Levels.at(intCurrentLevel-1)->getWidth(); x++)
	{
		for(int y = 0; y < vec_Levels.at(intCurrentLevel-1)->getHeight(); y++)
		{
			if (vec_Tiles.at(y).at(x).getVisible())// || vec_Tiles.at(y).at(x).getSeen())
			{
				move(y+2,x);
				chtype dungeonColor;
				if (etherealMode == true) {dungeonColor = COLOR_PAIR(7);}
				else {dungeonColor = COLOR_PAIR(1);}
				attron(dungeonColor);
				addch(vec_Levels.at(intCurrentLevel-1)->at(x,y));
				attron(dungeonColor);
			}
			/*else if (vec_Tiles.at(y).at(x).getSeen())
			{
				move(y+2,x);
				attron(COLOR_PAIR(5));
				addch(vec_Levels.at(intCurrentLevel-1)->at(x,y));
				attron(COLOR_PAIR(5));
			}*/
		}
	}
}
void Game::takeTurn()
{
	Command();
	
	if (player.getETurns() <= 0)
	{
		etherealMode = false;
		if (vec_Tiles.at(player.getYPos()).at(player.getXPos()).getWalkable() == false)
		{
			etherealDeath();
		}
	}

	if (etherealMode == false && gameOver == false)
	{
		spawnMonster();
		monsterTurn();

		//sets player health regen, mana regen, and oil consumption
		player.setPlayerLevels(lngTurns);
	}
	else
	{
		player.setETurns(player.getETurns() - 1);
	}

	lngTurns++;
	redrawScreen();
}
void Game::spawnMonster()
{
	bool bPlaced = false;

	if (mt()%200 == 0)
	{
		int loops = 0;

		while (!bPlaced && loops < 200)
		{
			int x = mt()%79;
			int y = mt()%20;
			int dist = (int)sqrt(pow((double)player.getXPos() - x, 2) + pow((double)player.getYPos() - y, 2));

			if (vec_Tiles.at(y).at(x).getTileCreature() == NULL &&
				vec_Tiles.at(y).at(x).getWalkable() == true
				&& vec_Tiles.at(y).at(x).getUpstairs() == false && vec_Tiles.at(y).at(x).getDownstairs() == false &&
				dist > 20)
			{
				Creature* tempCreature = cFac.generateCreature(intCurrentLevel);
				tempCreature->setXPos(x);
				tempCreature->setYPos(y);
				tempCreature->setHP(tempCreature->getMaxHP());
				vec_Tiles.at(y).at(x).setTileCreature(tempCreature);
				bPlaced = true;
			}

			loops++;
		}
	}
}
void Game::monsterTurn()
{
	for (int x = 0; x < 79; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			Creature* tempCreature = vec_Tiles.at(y).at(x).getTileCreature();
			if (tempCreature != NULL)
			{
				//if creature hasn't already performed an action
				if (tempCreature->getAction() == false)
				{
					int dist = (int)sqrt(pow((double)(player.getXPos() - tempCreature->getXPos()), 2) + pow((double)(player.getYPos() - tempCreature->getYPos()), 2));

					//if creature adjacent to player
					if((x+1 == player.getXPos() && y == player.getYPos()) || 
					(x-1 == player.getXPos() && y == player.getYPos()) || 
					(x == player.getXPos() && y+1 == player.getYPos()) || 
					(x == player.getXPos() && y-1 == player.getYPos()))
					{
						int intDmg = (mt()%(tempCreature->getLevel())*2)+1;

						Creature* playerCreature = dynamic_cast<Creature*>(&player);
						if (tempCreature->attack(playerCreature, intDmg))
						{
							vec_Messages.push_back("The " + tempCreature->getName() + " attacked you for " + to_string((long long)intDmg) + " damage");
							vec_Messages.push_back("The " + tempCreature->getName() + " killed you");
							gameOver = true;
						}
						else
						{
							vec_Messages.push_back("The " + tempCreature->getName() + " attacked you for " + to_string((long long)intDmg) + " damage");
						}
						tempCreature->setAction(true);
					}
					//if player is within range of the creature & the creature hasn't moved yet
					else if (dist < 17)
					{
						int oldX = tempCreature->getXPos();
						int oldY = tempCreature->getYPos();
						moveCreature(tempCreature, player.getXPos(), player.getYPos());
						int newX = tempCreature->getXPos();
						int newY = tempCreature->getYPos();
						if (newX != oldX || newY != oldY)
						{
							vec_Tiles.at(oldY).at(oldX).setWalkable(true);
							vec_Tiles.at(newY).at(newX).setWalkable(false);
							vec_Tiles.at(newY).at(newX).setTileCreature(tempCreature);
							vec_Tiles.at(y).at(x).setTileCreature(NULL);
						}
					}
				}
			}
		}
	}

	//set all creatures to have actions for next turn
	for (int x = 0; x < 79; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			Creature* tempCreature = vec_Tiles.at(y).at(x).getTileCreature();
			if (tempCreature != NULL)
			{
				tempCreature->setAction(false);
			}
		}
	}
}
void Game::moveCreature(Creature* &creature, int X, int Y)
{
	//TODO: Optimize code (or change to be faster somehow)
	Node* activeNode = new Node(creature->getXPos(), creature->getYPos());
	list_OpenNodes.push_back(activeNode);
	list<Node*>::iterator iOpen;
	list<Node*>::iterator iClosed;

	while (!list_OpenNodes.empty() && PathFound == false && list_ClosedNodes.size() < 45)
	{
		activeNode = list_OpenNodes.front();
		double tempF = activeNode->getF();

		for (iOpen = list_OpenNodes.begin(); iOpen != list_OpenNodes.end(); iOpen++)
		{
			if ((*iOpen)->getF() < tempF)
			{
				activeNode = (*iOpen);
			}
		}
		list_ClosedNodes.push_back(activeNode);

		//erase from open list
		list<Node*>::iterator iErase = list_OpenNodes.begin();
		bool erased = false;
		while (!erased)
		{
			if ((*iErase) == activeNode)
			{
				iErase = list_OpenNodes.erase(iErase);
				erased = true;
			}
			if (iErase != list_OpenNodes.end())
			{
				iErase++;
			}
		}

		if (activeNode->getX() == X && activeNode->getY() == Y)
		{
			PathFound = true;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				Node* neighborNode = new Node();
				if (i == 0)
				{
					neighborNode->setX(activeNode->getX());
					neighborNode->setY(activeNode->getY()-1);
				}
				else if (i == 1)
				{
					neighborNode->setX(activeNode->getX()+1);
					neighborNode->setY(activeNode->getY());
				}
				else if (i == 2)
				{
					neighborNode->setX(activeNode->getX());
					neighborNode->setY(activeNode->getY()+1);
				}
				else
				{
					neighborNode->setX(activeNode->getX()-1);
					neighborNode->setY(activeNode->getY());
				}

				int neighborX = neighborNode->getX();
				int neighborY = neighborNode->getY();

				if (neighborX < 79 && neighborX >= 0 && neighborY < 20 && neighborY >= 0)
				{
					//loops to determine which list a node is in
					for (iOpen = list_OpenNodes.begin(); iOpen != list_OpenNodes.end(); iOpen++)
					{
						if (neighborNode->getX() == (*iOpen)->getX() && neighborNode->getY() == (*iOpen)->getY())
						{
							delete neighborNode;
							neighborNode = (*iOpen);
							neighborNode->setListType('O');
						}
					}
					//only loop is not in open list already (saves a little time since closed list is much bigger)
					if (neighborNode->getListType() == 'X')
					{
						for (iClosed = list_ClosedNodes.begin(); iClosed != list_ClosedNodes.end(); iClosed++)
						{
							if (neighborNode->getX() == (*iClosed)->getX() && neighborNode->getY() == (*iClosed)->getY())
							{
								delete neighborNode;
								neighborNode = (*iClosed);
								neighborNode->setListType('C');
							}
						}
					}

					if (neighborNode->getListType() == 'X')
					{
					
						if (vec_Tiles.at(neighborY).at(neighborX).getWalkable() ||
							(player.getXPos() == neighborX && player.getYPos() == neighborY) ||
							vec_Tiles.at(neighborY).at(neighborX).getTileCreature() != NULL)
						{
							neighborNode->setParent(activeNode);

							//calculate F = G(cost to get to current tile) + H(heuristic to reach end tile)

							//I use the Manhattan distance since my program already runs on a grid and it slightly faster
							//It helps when there are multiple enemies
							double tempHCost = abs(neighborX - X) + abs(neighborY - Y);
							int tempGCost = neighborNode->getParent()->getG()+1;
							double tempFCost = tempHCost + tempGCost;
							neighborNode->setH(tempHCost);
							neighborNode->setG(tempGCost);
							neighborNode->setF(tempFCost);

							list_OpenNodes.push_back(neighborNode);
						}
						else
						{
							list_ClosedNodes.push_back(neighborNode);
						}
					}
				}
				else
				{
					delete neighborNode;
				}
			}
		}
	}

	if (PathFound == true)
	{
		//create path
		while (activeNode->getParent() != NULL)
		{
			list_Path.push_back(activeNode);
			activeNode = activeNode->getParent();
		}

		//move creature
		if (vec_Tiles.at(list_Path.back()->getY()).at(list_Path.back()->getX()).getTileCreature() == NULL)
		{
			creature->setXPos(list_Path.back()->getX());
			creature->setYPos(list_Path.back()->getY());
			creature->setAction(true);
		}
	}

	//clear vectors
	while (!list_OpenNodes.empty())
	{
		delete list_OpenNodes.back();
		list_OpenNodes.pop_back();
	}
	while (!list_ClosedNodes.empty())
	{
		delete list_ClosedNodes.back();
		list_ClosedNodes.pop_back();
	}
	list_Path.clear();

	PathFound = false;
}
void Game::setTilesInvisible(vector<vector<char> > &vec_TempTiles)
{
	for(int x = 0; x < vec_Levels.at(intCurrentLevel-1)->getWidth(); x++)
	{
		for(int y = 0; y < vec_Levels.at(intCurrentLevel-1)->getHeight(); y++)
		{
			if (vec_TempTiles.at(y).at(x) == 'X')
			{
				vec_Tiles.at(y).at(x).setVisible(true);
				vec_Tiles.at(y).at(x).setSeen(true);
			}
			else
			{
				vec_Tiles.at(y).at(x).setVisible(false);
			}
			vec_TempTiles.at(y).at(x) = ' ';
		}
	}
}
void Game::setTilesVisible(vector<vector<char> > &vec_TempTiles, int x, int y, int direction, int range)
{
	if (etherealMode == true)
	{
		for (int x = 0; x < 79; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				int dist = (int)sqrt(pow((double)player.getXPos() - x, 2) + pow((double)player.getYPos() - y, 2));
				if (dist < 10)
				{
					vec_TempTiles.at(y).at(x) = 'X';
				}
			}
		}
	}
	else
	{
		if (x < 79 && x >= 0 && y < 20 && y >= 0 && range > 0)
		{
			if (!vec_Tiles.at(y).at(x).getWalkable() && direction != -1)
			{
				vec_TempTiles.at(y).at(x) = 'X';
			}
			else if (direction == -1)	//starting point
			{
				vec_TempTiles.at(y).at(x) = 'X';
				setTilesVisible(vec_TempTiles, x, y-1, 0, range);
				setTilesVisible(vec_TempTiles, x+1, y, 1, range);
				setTilesVisible(vec_TempTiles, x, y+1, 2, range);
				setTilesVisible(vec_TempTiles, x-1, y, 3, range);
			}
			else if (direction == 0)	//up
			{
				vec_TempTiles.at(y).at(x) = 'X';
				setTilesVisible(vec_TempTiles, x, y-1, 0, range-1);
				if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '.' &&
					(vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '.' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '>' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '<'))
				{
					range -= 2;
				}
				else
				{
					range -= 8;
				}
				setTilesVisible(vec_TempTiles, x+1, y, 0, range);
				setTilesVisible(vec_TempTiles, x-1, y, 0, range);
			}
			else if (direction == 1)	//right
			{
				vec_TempTiles.at(y).at(x) = 'X';
				setTilesVisible(vec_TempTiles, x+1, y, 1, range-1);
				if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '.' &&
					(vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '.' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '>' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '<'))
				{
					range -= 2;
				}
				else
				{
					range -= 8;
				}
				setTilesVisible(vec_TempTiles, x, y-1, 1, range);
				setTilesVisible(vec_TempTiles, x, y+1, 1, range);
			}
			else if (direction == 2)	//down
			{
				vec_TempTiles.at(y).at(x) = 'X';
				setTilesVisible(vec_TempTiles, x, y+1, 2, range-1);
				if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '.' &&
					(vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '.' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '>' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '<'))
				{
					range -= 2;
				}
				else
				{
					range -= 8;
				}
				setTilesVisible(vec_TempTiles, x+1, y, 2, range);
				setTilesVisible(vec_TempTiles, x-1, y, 2, range);
			}
			else if (direction == 3)	//left
			{
				vec_TempTiles.at(y).at(x) = 'X';
				setTilesVisible(vec_TempTiles, x-1, y, 3, range-1);
				if (vec_Levels.at(intCurrentLevel-1)->at(x,y) == '.' &&
					(vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '.' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '>' ||
					vec_Levels.at(intCurrentLevel-1)->at(player.getXPos(),player.getYPos()) == '<'))
				{
					range -= 2;
				}
				else
				{
					range -= 8;
				}
				setTilesVisible(vec_TempTiles, x, y+1, 3, range);
				setTilesVisible(vec_TempTiles, x, y-1, 3, range);
			}
		}
	}
}
void Game::displayItems(int currentTab, bool &TakenAction)
{
	vector<Item*> vec_TempPlayerInv = player.getInventory();
	vector<Item*> vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();
	int invSlot = 0;

	chtype itemSelectionColor = COLOR_PAIR(6);
	string strBoxTemp;
	int currentXSel = 0;
	int currentYSel = 0;
	int startingX = 0;
	int startingY = 0;
	int offsetX = 0;
	int offsetY = 0;
	int boxXSel = 0;
	int boxYSel = 0;
	int invColumns = 0;
	int invRows = 0;

	do
	{
		clear();
		vec_TempPlayerInv = player.getInventory();
		vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();

		for (int x = 3; x < 97; x++)
		{
			for (int y = 3; y < 26; y++)
			{
				if (y == 3 || y == 25)
				{
					strBoxTemp = "-";
				}
				else if (x == 3 || x == 96)
				{
					strBoxTemp = "|";
				}
				else
				{
					strBoxTemp = " ";
				}
				outputText(strBoxTemp, x, y);
			}
		}

		outputText("|", 3, 2);
		outputText(".----------.", 3, 1);
		outputText("BACKPACK", 5, 2);
		outputText("|", 14, 2);

		outputText("|", 15, 2);
		outputText(".----------.", 15, 1);
		outputText("EQUIPPED", 17, 2);
		outputText("|", 26, 2);

		outputText("|", 27, 2);
		outputText(".------.", 27, 1);
		outputText("TILE", 29, 2);
		outputText("|", 34, 2);

		//tab 1 (backpack)
		if (currentTab == 0)
		{
			outputText("|          `", 3, 3);

			startingX = 6;
			startingY = 5;
			offsetX = 6;
			offsetY = 6;
			boxXSel = 0;
			boxYSel = 0;
			invColumns = 7;
			invRows = 3;
			invSlot = 0;

			for (int x = startingX; x < startingX+(6*invColumns); x+=offsetX)
			{
				for (int y = startingY; y < startingY+(6*invRows); y+=offsetY)
				{
					//draw backpack square
					if (currentXSel == boxXSel && currentYSel == boxYSel) {attron(itemSelectionColor);}
					outputText("-----", x, y);
					outputText("|   |", x, y+1);
					outputText("|   |", x, y+2);
					outputText("|   |", x, y+3);
					outputText("-----", x, y+4);

					invSlot = (7*boxYSel) + boxXSel;
					int invSize = vec_TempPlayerInv.size();

					if (invSlot < invSize)
					{
						outputText(string(1, vec_TempPlayerInv.at(invSlot)->getDisplayChar()), x+2, y+2);
					}

					attroff(itemSelectionColor);

					boxYSel++;
				}
				boxXSel++;
				boxYSel = 0;
			}

		}
		//tab 2 (equipped)
		else if (currentTab == 1)
		{
			outputText("'          `", 15, 3);


		}
		//tab 3 (items on tile)
		else if (currentTab == 2)
		{
			outputText("'      `", 27, 3);

			startingX = 6;
			startingY = 5;
			offsetX = 6;
			offsetY = 6;
			boxXSel = 0;
			boxYSel = 0;
			invColumns = 7;
			invRows = 3;
			invSlot = 0;

			for (int x = startingX; x < startingX+(6*invColumns); x+=offsetX)
			{
				for (int y = startingY; y < startingY+(6*invRows); y+=offsetY)
				{
					//draw backpack square
					if (currentXSel == boxXSel && currentYSel == boxYSel) {attron(itemSelectionColor);}
					outputText("-----", x, y);
					outputText("|   |", x, y+1);
					outputText("|   |", x, y+2);
					outputText("|   |", x, y+3);
					outputText("-----", x, y+4);

					invSlot = (7*boxYSel) + boxXSel;
					int invSize = vec_TempTileInv.size();

					if (invSlot < invSize)
					{
						outputText(string(1, vec_TempTileInv.at(invSlot)->getDisplayChar()), x+2, y+2);
					}

					attroff(itemSelectionColor);

					boxYSel++;
				}
				boxXSel++;
				boxYSel = 0;
			}
		}

		refresh();

		char_Button = wgetch(curWin);
		Item* currentItem = NULL;
		invSlot = (7*currentYSel) + currentXSel;
		switch(char_Button)
		{
			case '1':
			{
				currentTab = 0;
				break;
			}
			case '2':
			{
				currentTab = 1;
				break;
			}
			case '3':
			{
				currentTab = 2;
				break;
			}
			case 'a':
			{
				if (currentTab > 0)
				{
					currentTab--;
				}
				break;
			}
			case 'd':
			{
				if (currentTab < 2)
				{
					currentTab++;
				}
				break;
			}
			case 'e':
			{
				int invSize = 0;
				vector<Item*> tempInv;
				if (currentTab == 0)
				{
					invSize = vec_TempPlayerInv.size();
					tempInv = vec_TempPlayerInv;
				}
				else if (currentTab == 2)
				{
					invSize = vec_TempTileInv.size();
					tempInv = vec_TempTileInv;
				}
				if (invSlot < invSize && (currentTab == 0 || currentTab == 2))
				{
					currentItem = tempInv.at(invSlot);
				}
				if (currentItem != NULL)
				{
					equipItem(currentItem, invSlot, currentTab, TakenAction);
				}
				break;
			}
			case 'u':
			{
				int invSize = 0;
				vector<Item*> tempInv;
				if (currentTab == 0)
				{
					invSize = vec_TempPlayerInv.size();
					tempInv = vec_TempPlayerInv;
				}
				else if (currentTab == 2)
				{
					invSize = vec_TempTileInv.size();
					tempInv = vec_TempTileInv;
				}
				if (invSlot < invSize && (currentTab == 0 || currentTab == 2))
				{
					currentItem = tempInv.at(invSlot);
				}
				if (currentItem != NULL)
				{
					useItem(currentItem, invSlot, currentTab, TakenAction);
				}
				break;
			}
			case 't':
			{
				if ((currentTab == 0 || currentTab == 1) && invSlot < (signed)vec_TempPlayerInv.size())
				{
					currentItem = vec_TempPlayerInv.at(invSlot);
					tossItem(currentItem, invSlot, TakenAction);
				}
				break;
			}
			case 'p':
			{
				if (currentTab == 2 && invSlot < (signed)vec_TempTileInv.size())
				{
					currentItem = vec_TempTileInv.at(invSlot);
					pickupItem(currentItem, invSlot, TakenAction);
				}
				break;
			}

			case 2:
			{
				if (currentYSel < invRows-1)
				{
					currentYSel++;
				}
				break;
			}
			case 3:
			{
				if (currentYSel > 0)
				{
					currentYSel--;
				}
				break;
			}
			case 4:
			{
				if (currentXSel > 0)
				{
					currentXSel--;
				}
				break;
			}
			case 5:
			{
				if (currentXSel < invColumns-1)
				{
					currentXSel++;
				}
				break;
			}
		}
	}
	while(char_Button != 'i');
}
void Game::pickupItem(Item* &tempItem, int vecPos, bool &TakenAction)
{
	vector<Item*> vec_TempPlayerInv = player.getInventory();
	vector<Item*> vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();

	if (tempItem->getName() != "gold")
	{
		vec_Messages.push_back("You picked up " + itemArticleName(tempItem) + " " + tempItem->getName() + "!");
		vec_TempPlayerInv.push_back(tempItem);
		player.setInventory(vec_TempPlayerInv);
		vec_TempTileInv.erase(vec_TempTileInv.begin()+vecPos);
		vec_Tiles.at(player.getYPos()).at(player.getXPos()).setTileItemsVector(vec_TempTileInv);
	}
	else
	{
		vec_Messages.push_back("You picked up " + to_string((long long)tempItem->getValue()) + " gold!");
		player.setGold(player.getGold() + tempItem->getValue());
		vec_TempTileInv.erase(vec_TempTileInv.begin()+vecPos);
		vec_Tiles.at(player.getYPos()).at(player.getXPos()).setTileItemsVector(vec_TempTileInv);
		delete tempItem;
	}

	TakenAction = true;
}
void Game::tossItem(Item* &tempItem, int vecPos, bool &TakenAction)
{
	vector<Item*> vec_TempPlayerInv = player.getInventory();
	vector<Item*> vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();

	vec_Messages.push_back("You tossed the " + tempItem->getName() + " on the ground");
	vec_TempTileInv.push_back(tempItem);
	vec_Tiles.at(player.getYPos()).at(player.getXPos()).setTileItemsVector(vec_TempTileInv);
	vec_TempPlayerInv.erase(vec_TempPlayerInv.begin()+vecPos);
	player.setInventory(vec_TempPlayerInv);

	TakenAction = true;
}
void Game::equipItem(Item* &tempItem, int vecPos, int itemLocation, bool &TakenAction)
{

}
void Game::useItem(Item* &tempItem, int vecPos, int itemLocation, bool &TakenAction)
{
	//itemLocation: 0=player, 2=tile
	string strMessage;
	bool successfulUse = tempItem->use(player, strMessage);
	vector<Item*> vec_TempPlayerInv = player.getInventory();
	vector<Item*> vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();

	vec_Options.clear();
	vec_Options.push_back("OK");
	popupMessage(strMessage,
		vec_Options, 0, false, strNOMESSAGE, 0);

	if (itemLocation == 0 && successfulUse)
	{
		vec_Messages.push_back(strMessage);
		//remove item from player inventory
		vec_TempPlayerInv.erase(vec_TempPlayerInv.begin()+vecPos);
		player.setInventory(vec_TempPlayerInv);
		delete tempItem;
		TakenAction = true;
	}
	else if (itemLocation == 2 && successfulUse)
	{
		vec_Messages.push_back(strMessage);
		//remove item from tile inventory
		vec_TempTileInv.erase(vec_TempTileInv.begin()+vecPos);
		vec_Tiles.at(player.getYPos()).at(player.getXPos()).setTileItemsVector(vec_TempTileInv);
		delete tempItem;
		TakenAction = true;
	}
	redrawScreen();
}
void Game::playerAttack(int monsterX, int monsterY)
{
	//TODO: Add ranged attacks
	Creature* tempCreature = vec_Tiles.at(monsterY).at(monsterX).getTileCreature();
	if (player.attack(tempCreature, player.getLevel() + (int)(player.getStr()/2)))
	{
		vec_Messages.push_back("You attacked the " + tempCreature->getName());
		vec_Messages.push_back("You have slain the " + tempCreature->getName() + "!");
		player.setExPoints(player.getExPoints() + (tempCreature->getLevel() * 2));
		vec_Tiles.at(tempCreature->getYPos()).at(tempCreature->getXPos()).setWalkable(true);
		//TODO: Add monster drops
		delete tempCreature;
		vec_Tiles.at(monsterY).at(monsterX).setTileCreature(NULL);
		if (player.getLevel() > playerLevel)
		{
			string levelUpMessage = "You have leveled up to level " + to_string((long long)player.getLevel()) + "!";
			vec_Messages.push_back(levelUpMessage);
			vec_Options.clear();
			vec_Options.push_back("OK");
			popupMessage(levelUpMessage, vec_Options, 0, false, strNOMESSAGE, 0);
			characterLevelUp("current", 10);
			playerLevel = player.getLevel();
		}
	}
	else
	{
		vec_Messages.push_back("You attacked the " + tempCreature->getName());
	}
}
void Game::playerMove(int playerNewX, int playerNewY, bool &TakenAction)
{
	if (playerNewX >= 0 && playerNewX <= 78 && playerNewY >= 0 && playerNewY <= 19)
	{
		if (etherealMode == true)
		{
			player.setXPos(playerNewX);
			player.setYPos(playerNewY);
			TakenAction = true;
		}
		else if (player.canMove(playerNewX, playerNewY, vec_Tiles))
		{
			player.setXPos(playerNewX);
			player.setYPos(playerNewY);
			if (vec_Tiles.at(playerNewY).at(playerNewX).getTileItemsVector().size() > 1)
			{
				str_Update = "There are multiple items around you.";
				newUpdate = true;
			}
			else if (vec_Tiles.at(playerNewY).at(playerNewX).getTileItemsVector().size() == 1)
			{
				Item* tempItem = vec_Tiles.at(playerNewY).at(playerNewX).getTileItemsVector().at(0);
				str_Update = "There is " + itemArticleName(tempItem) + " " + tempItem->getName() + " at your feet";
				newUpdate = true;
			}
			TakenAction = true;
		}
		else if (vec_Tiles.at(playerNewY).at(playerNewX).getTileCreature() != NULL)
		{
			playerAttack(playerNewX, playerNewY);
			TakenAction = true;
		}
	}
}
void Game::etherealDeath()
{
	if (vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileCreature() != NULL)
	{
		Creature* tempCreature = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileCreature();
		vec_Messages.push_back("You have violently dematerialized inside of a " + tempCreature->getName() + "!");
		if (player.attack(tempCreature, 10000000))
		{
			vec_Messages.push_back("You have slain the " + tempCreature->getName() + "!");
			player.setExPoints(player.getExPoints() + (tempCreature->getLevel() * 2));
			vec_Tiles.at(tempCreature->getYPos()).at(tempCreature->getXPos()).setWalkable(true);
			delete vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileCreature();
			vec_Tiles.at(player.getYPos()).at(player.getXPos()).setTileCreature(NULL);
		}
	}
	else
	{
		vec_Messages.push_back("You have violently dematerialized inside of a wall!");
	}
	player.setHP(0);
	gameOver = true;
}
void Game::Command()
{
	bool TakenAction = false;

	do
	{
		char_Button = wgetch(curWin);

		switch(char_Button)
		{
			case 'a':
			{
				playerMove(player.getXPos() - 1, player.getYPos(), TakenAction);
				break;
			}
			case 'd':
			{
				playerMove(player.getXPos() + 1, player.getYPos(), TakenAction);
				break;
			}
			case 'w':
			{
				playerMove(player.getXPos(), player.getYPos() - 1, TakenAction);
				break;
			}
			case 's':
			{
				playerMove(player.getXPos(), player.getYPos() + 1, TakenAction);
				break;
			}
			case 'x':
			{
				if (etherealMode == true)
				{
					etherealMode = false;
					if (vec_Tiles.at(player.getYPos()).at(player.getXPos()).getWalkable() == false)
					{
						etherealDeath();
					}
					TakenAction = true;
				}
				else if (player.getETurns() > 0)
				{
					etherealMode = true;
					vec_Tiles.at(player.getYPos()).at(player.getXPos()).setWalkable(true);
					TakenAction = true;
				}
				else
				{

				}
				break;
			}
			case 'z':
			{
				TakenAction = true;
				break;
			}
			case '<':
			{
				if (vec_Tiles.at(player.getYPos()).at(player.getXPos()).getUpstairs() && etherealMode == false)
				{
					if (intCurrentLevel == 1)
					{
						int intChoice = 0;
						vec_Options.clear();
						vec_Options.push_back("Yes");
						vec_Options.push_back("No");
						intChoice = popupMessage("Are you sure you want to leave the dungeon?",
							vec_Options, 1, false, strNOMESSAGE, 0);

						if (intChoice == 0)
						{
							gameOver = true;
							TakenAction = true;
						}
						else
						{
							vec_Options.clear();
							vec_Options.push_back("YEAH!");
							popupMessage("You're not going to let the dungeon scare you!",
								vec_Options, 0, false, strNOMESSAGE, 0);
							redrawScreen();
						}
					}
					else
					{
						changeLevel(-1);
						TakenAction = true;
					}
				}
				break;
			}
			case '>':
			{
				if (vec_Tiles.at(player.getYPos()).at(player.getXPos()).getDownstairs() && etherealMode == false)
				{
					changeLevel(1);
					TakenAction = true;
				}
				break;
			}
			case 'u':
			{
				if (etherealMode == false)
				{
					vector<Item*> vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();
					int vecPos = 0;
					Item* tempItem = NULL;

					if (vec_TempTileInv.size() > 1)
					{
						displayItems(2, TakenAction);
					}
					else if (vec_TempTileInv.size() == 1)
					{
						tempItem = vec_TempTileInv.at(0);
					}
					if (tempItem != NULL)
					{
						useItem(tempItem, vecPos, 2, TakenAction);
					}
				}
				break;
			}
			case 'p':
			{
				if (etherealMode == false)
				{
					vector<Item*> vec_TempTileInv = vec_Tiles.at(player.getYPos()).at(player.getXPos()).getTileItemsVector();
					int vecPos = 0;
					Item* tempItem = NULL;

					if (vec_TempTileInv.size() > 1)
					{
						displayItems(2, TakenAction);
					}
					else if (vec_TempTileInv.size() == 1)
					{
						tempItem = vec_TempTileInv.at(0);
					}
					if (tempItem != NULL)
					{
						pickupItem(tempItem, vecPos, TakenAction);
					}
				}
				break;
			}
			case 'i':
			{
				if (etherealMode == false)
				{
					displayItems(0, TakenAction);
					TakenAction = true;
				}
				break;
			}

			case 'f':
			{
				if (etherealMode == false)
				{
					if (player.hasLantern())
					{
						player.lanternState();
						TakenAction = true;
					}
					else
					{
						str_Update = "You don't have a lantern.";
						newUpdate = true;
						drawMessages();
					}
				}
			}

			case 3: //KEY_UP
			{
				if (intCurrentMessageLine >= 0 && !vec_Messages.empty())
				{
					intCurrentMessageLine--;
					drawMessages();
				}
				break;
			}
			case 2: //KEY_DOWN
			{
				if (intCurrentMessageLine < (signed)vec_Messages.size() - 1)
				{
					intCurrentMessageLine++;
					drawMessages();
				}
				break;
			}

			//TODO: Add save button

			default:
			{
				str_Update = "Unknown command: " + string(1, char_Button);
				newUpdate = true;
				drawMessages();
				break;
			}
		}
	}
	while (!TakenAction);
}