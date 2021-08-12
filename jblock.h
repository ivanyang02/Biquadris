#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class JBlock : public Block {
	int position;
	public:
		JBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
