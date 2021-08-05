#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class ZBlock : public Block {
	public:
		ZBlock(std::vector<std::vector<Cell *>> board, int level);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
