#ifndef _IBLOCK_H_
#define _IBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class IBlock : public Block {
	bool vertical;
	public:
		IBlock(std::vector<std::vector<Cell *>> board, int level);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
