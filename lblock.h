#ifndef _LBLOCK_H_
#define _LBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class LBlock : public Block {
	int position; //Records which position the LBlock is in out of the 4 possible positions
	public:
		LBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col); //LBlock constructor
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
		//Rotates the LBlock clockwise and counterclockwise according to the direction on the given board
};

#endif
