#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include <iostream>
#include <vector>
#include <memory>

#include "block.h"

class JBlock : public Block {
	int position;
	public:
		JBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level);
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
};

#endif
