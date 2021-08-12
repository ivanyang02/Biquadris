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
        std::vector<char> sequence;
		int seqIndex = 0;
		Block *currentBlock;
		char nextBlock;
		Xwindow *window;
		std::vector<std::vector<Cell *>>board;
	public:
		Board(int player, std::vector<char> seq, Xwindow *w);
		~Board();
		bool NewBlock();
		bool AddBlock(char type);
		void Move(char direction);
		void Rotate(char direction);
		bool Drop();
		int ClearLine(int row);
		void LevelUp();
		void LevelDown();
		std::vector<std::vector<Cell *>> GetBoard() const;
		char GetCellType(int row, int col) const;
		int GetRows() const;
		int GetCols() const;
		int GetLevel() const;
		int GetScore() const;
		char GetNext() const;
		bool GetBlind() const;
		void SetBlind();
		friend std::ostream &operator<<(std::ostream &out, const Board &b);		
};

#endif
