#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class JBlock : public Block {
	public:
		int position;
		JBlock(std::vector<std::vector<Cell *>> board, int level);
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
};

#endif
