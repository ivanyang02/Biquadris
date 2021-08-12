#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <vector>

#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "cell.h"
#include "window.h"

class Board {
		int player;
		int rows = 15;
		int cols = 11;
		int extra = 3;
		int currentLevel = 0;
		int level4Count = 0;
		int score = 0;
		bool blind = false;
		bool heavy = false;
        std::vector<char> sequence;
		int seqIndex = 0;
		Block *currentBlock;
		char nextBlock;
		Xwindow *window;
		std::vector<std::vector<Cell *>>board;
	public:
		Board(int player, std::vector<char> seq, Xwindow *w); //board contsructor
		~Board(); //board destructor
		bool NewBlock(); //generates the new type of block considering level and block sequences, and rng, and passes type into AddBlock
		bool AddBlock(char type, int row, int col); //Given type and location, adds the proper cells to a block
		bool ChangeBlock(char type); 
		void Move(char direction); //Calls block move on the current block
		void Rotate(char direction); //Calls block rotate on the current block
		bool Drop(); //Calls block drop on the current block
		bool HeavyDrop(); //Implements the special action heavy drop
		int ClearLine(int row); //Clears lines that are full
		void LevelUp(); //Increases the current level
		void LevelDown(); //Decreases the current level
		std::vector<std::vector<Cell *>> GetBoard() const; //retrieves the board field
		char GetCellType(int row, int col) const; //returns the cell type at the given location
		int GetRows() const; //returns the rows
		int GetCols() const; //returns the columns
		int GetLevel() const; //returns the level
		int GetScore() const; //returns the score
		char GetNext() const; //returns the type of the next block
		bool GetBlind() const; //returns wether the special action blind is on
		void SetBlind(); //sets the board to blind
		void SetHeavy(); //sets the board to heavy
		friend std::ostream &operator<<(std::ostream &out, const Board &b); //prints out the board
};

#endif
