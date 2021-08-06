#include "oblock.h"

OBlock::OBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('O');
	SetLevel(level);
    SetPosition(14, 0);
	board[15][0]->SetType('O');
	board[15][0]->SetOwner(this);
	board[15][1]->SetType('O');
	board[15][1]->SetOwner(this);
	board[14][0]->SetType('O');
	board[14][0]->SetOwner(this);
	board[14][1]->SetType('O');
	board[14][1]->SetOwner(this);
	AddCell(board[15][0]);
	AddCell(board[15][1]);
	AddCell(board[14][0]);
	AddCell(board[14][1]);
}

void OBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
}
