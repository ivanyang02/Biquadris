#ifndef _TBLOCK_H_
#define _TBLOCK_H_

#include <iostream>
#include <vector>
#include <memory>

#include "block.h"

class TBlock : public Block {
	int position;
	public:
		TBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level);
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
};

#endif
