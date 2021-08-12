#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class SBlock : public Block {
	bool vertical; //True of the SBlock is vertical, false if horizontal
	public:
		SBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col); //SBlock constructor
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
		//Rotates the SBlock, flipping between the 2 possible positions
};

#endif
