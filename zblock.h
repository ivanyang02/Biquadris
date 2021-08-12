#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class ZBlock : public Block {
	bool vertical; //True if the ZBlock is vertical, false if horizontal
	public:
		ZBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col); //ZBlock constructor
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
		//Rotates the ZBlock by flipping between the two possible positions
};

#endif
