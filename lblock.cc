#include "lblock.h"

LBlock::LBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('L');
	SetLevel(level);
	board[14][0]->SetType('L');
	board[14][0]->SetOwner(this);
	board[14][1]->SetType('L');
	board[14][1]->SetOwner(this);
	board[14][2]->SetType('L');
	board[14][2]->SetOwner(this);
	board[15][2]->SetType('L');
	board[15][2]->SetOwner(this);
	AddCell(board[14][0]);
	AddCell(board[14][1]);
	AddCell(board[14][2]);
	AddCell(board[15][2]);
}

void LBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::cout << "lblockrotate " << direction << std::endl;
}
