#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class SBlock : public Block {
	public:
		SBlock(std::vector<std::vector<Cell *>> board, int level);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
