#include "oblock.h"

OBlock::OBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col)
{
	SetType('O');
	SetLevel(level);
	SetPosition(row, col);
	try {
	AddCell(board[row + 1][col]);
	AddCell(board[row + 1][col + 1]);
	AddCell(board[row][col]);
	AddCell(board[row][col + 1]);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void OBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
}
