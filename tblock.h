#ifndef _TBLOCK_H_
#define _TBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class TBlock : public Block {
	int position; //Records the position of the TBlock out of the 4 possible positions
	public:
		TBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col); //TBlock constructor
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
		//Rotates the TBlock clockwise and counterclockwise according to the direction on the given board
};

#endif
