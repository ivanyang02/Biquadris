#include "zblock.h"

ZBlock::ZBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('Z');
	SetLevel(level);
	board[15][0]->SetType('Z');
	board[15][0]->SetOwner(this);
	board[15][1]->SetType('Z');
	board[15][1]->SetOwner(this);
	board[14][1]->SetType('Z');
	board[14][1]->SetOwner(this);
	board[14][2]->SetType('Z');
	board[14][2]->SetOwner(this);
	AddCell(board[15][0]);
	AddCell(board[15][1]);
	AddCell(board[14][1]);
	AddCell(board[14][2]);
}

void ZBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::cout << "zblockrotate " << direction << std::endl;
}
