#ifndef _OBLOCK_H_
#define _OBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class OBlock : public Block {
	public:
		OBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col); //OBlock constructor
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
		//Does nothing, as rotating a square leaves it in the original position
};

#endif
