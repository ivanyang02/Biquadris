#ifndef _LBLOCK_H_
#define _LBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class LBlock : public Block {
	int position;
	public:
		LBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
