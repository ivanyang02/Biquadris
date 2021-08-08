#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_

#include <iostream>
#include <vector>
#include <memory>

#include "block.h"

class ZBlock : public Block {
	bool vertical;
	public:
		ZBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level);
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
};

#endif
