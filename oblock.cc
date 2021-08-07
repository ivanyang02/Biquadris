#include "oblock.h"

OBlock::OBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('O');
	SetLevel(level);
	SetPosition(14, 0);
	try {
	AddCell(board[15][0]);
	AddCell(board[15][1]);
	AddCell(board[14][0]);
	AddCell(board[14][1]);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void OBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
}
