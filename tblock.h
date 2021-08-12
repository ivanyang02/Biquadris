#ifndef _TBLOCK_H_
#define _TBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class TBlock : public Block {
	int position;
	public:
		TBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
