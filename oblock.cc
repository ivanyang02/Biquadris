#include "oblock.h"

OBlock::OBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col)
{
	SetType('O');
	SetLevel(level);
	SetPosition(row, col);
	try {
	AddCell(board[row + 1][col].get());
	AddCell(board[row + 1][col + 1].get());
	AddCell(board[row][col].get());
	AddCell(board[row][col + 1].get());
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void OBlock::Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) {
}
