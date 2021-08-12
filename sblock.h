#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class SBlock : public Block {
	bool vertical;
	public:
		SBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
