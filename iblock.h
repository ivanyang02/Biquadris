#ifndef _IBLOCK_H_
#define _IBLOCK_H_

#include <iostream>
#include <vector>

#include "block.h"

class IBlock : public Block {
	bool vertical; //True if the IBlock is vertical, false if horizontal
	public:
		IBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col); //IBlock constructor
		void Rotate(char direction, std::vector<std::vector<Cell *>> board) override;	
		//Rotates the IBlock clockwise and counterclockwise according to the direction on the given board
};

#endif
