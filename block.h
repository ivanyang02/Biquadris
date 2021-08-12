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
		virtual ~Block(); //virtual distructor for abstract class
		virtual int GetLevel(); //returns the level field of the object instance
		virtual int GetCoRow(); //returns the cornerRow of the object instance
		virtual int GetCellsCount(); //returns the number of cells in vector cells
		virtual void SetLevel(int level); //sets the level field
		virtual void SetType(char type); //sets the type field
		virtual void SetPosition(int row, int col); //sets both the cornerRow and cornerCol fields
		virtual void AddCell(Cell *cell); //adds the cell to the vector of cells
		virtual void RemoveCell(Cell *cell); //removes the specified cell from the vector of cells if present
		virtual void RemoveAll(); //removes all the cells in the vector of cells
		virtual bool Move(char direction, std::vector<std::vector<Cell *>> board);
		//shifts the block on position right, left, or down depending on the direction parameter on the given board, if it cannot move it does nothing
		virtual void Rotate(char direction, std::vector<std::vector<Cell *>> board) = 0;
		//rotates the block clockwise or counterclockwise depending on the direction parameter on the given board, if it cannot move it does nothing
		virtual void Drop(std::vector<std::vector<Cell *>> board);
		//moves the block down until it cannot move
};

#endif
