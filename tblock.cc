#include "tblock.h"

TBlock::TBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('T');
	SetLevel(level);
	board[14][1]->SetType('T');
	board[14][1]->SetOwner(this);
	board[15][0]->SetType('T');
	board[15][0]->SetOwner(this);
	board[15][1]->SetType('T');
	board[15][1]->SetOwner(this);
	board[15][2]->SetType('T');
	board[15][2]->SetOwner(this);
	AddCell(board[14][1]);
	AddCell(board[15][0]);
	AddCell(board[15][1]);
	AddCell(board[15][2]);
}

void TBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::cout << "tblockrotate " << direction << std::endl;
}
