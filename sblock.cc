#include "sblock.h"

SBlock::SBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('S');
	SetLevel(level);
	board[14][0]->SetType('S');
	board[14][0]->SetOwner(this);
	board[14][1]->SetType('S');
	board[14][1]->SetOwner(this);
	board[15][1]->SetType('S');
	board[15][1]->SetOwner(this);
	board[15][2]->SetType('S');
	board[15][2]->SetOwner(this);
	AddCell(board[14][0]);
	AddCell(board[14][1]);
	AddCell(board[15][1]);
	AddCell(board[15][2]);
}

void SBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::cout << "sblockrotate " << direction << std::endl;
}
