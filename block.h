#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>

#include "cell.h"

class Block {
		char type;
		int level;
		int cellsCount = 0;
	protected:
		int cornerRow;
		int cornerCol;
		std::vector<Cell *> cells;
	public:
		//virtual Block(char type, Cell *board[18][11]) = 0;
		virtual ~Block();
		virtual int GetLevel();
		virtual int GetCoRow();
		virtual int GetCellsCount();
		virtual void SetLevel(int level);
		virtual void SetType(char type);
		virtual void SetPosition(int row, int col);
		virtual void AddCell(Cell *cell);
		virtual void RemoveCell(Cell *cell);
		virtual bool Move(char direction, std::vector<std::vector<Cell *>> board);
		virtual void Rotate(char direction, std::vector<std::vector<Cell *>> board) = 0;
		virtual void Drop(std::vector<std::vector<Cell *>> board);
};

#endif
