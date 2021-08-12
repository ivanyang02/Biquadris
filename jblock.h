#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class JBlock : public Block {
	int position; //records the 4 possible positions
	public:
		JBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col); //JBlock constructor
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;
		//Rotates the Jblock clockwise and counterclockwise according to the direction on the given board
};

#endif
