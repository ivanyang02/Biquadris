#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include <iostream>
#include <vector>
#include <memory>

#include "block.h"

class SBlock : public Block {
	bool vertical;
	public:
		SBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level);
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
};

#endif
