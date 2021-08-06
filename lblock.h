#ifndef _LBLOCK_H_
#define _LBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class LBlock : public Block {
	public:
		int position;
		LBlock(std::vector<std::vector<Cell *>> board, int level);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
