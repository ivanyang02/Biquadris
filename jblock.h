#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class JBlock : public Block {
	int position; //Records the position of the JBlock out of the 4 possible positions
	public:
		JBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col); //JBlock constructor
		void Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) override;
		//Rotates the Jblock clockwise and counterclockwise according to the direction on the given board
};

#endif
