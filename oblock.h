#ifndef _OBLOCK_H_
#define _OBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class OBlock : public Block {
	public:
		OBlock(std::vector<std::vector<Cell *>> board, int level);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
