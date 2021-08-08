#ifndef _LBLOCK_H_
#define _LBLOCK_H_

#include <iostream>
#include <vector>
#include <memory>

#include "block.h"

class LBlock : public Block {
	int position;
	public:
		LBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level);
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
};

#endif
