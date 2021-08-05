#include "jblock.h"

JBlock::JBlock(std::vector<std::vector<Cell *>> board, int level)
{
	SetType('J');
	SetLevel(level);
	board[15][0]->SetType('J');
	board[15][0]->SetOwner(this);
	board[14][0]->SetType('J');
	board[14][0]->SetOwner(this);
	board[14][1]->SetType('J');
	board[14][1]->SetOwner(this);
	board[14][2]->SetType('J');
	board[14][2]->SetOwner(this);
	AddCell(board[15][0]);
	AddCell(board[14][0]);
	AddCell(board[14][1]);
	AddCell(board[14][2]);
}

void JBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::cout << "jblockrotate " << direction << std::endl;
}
