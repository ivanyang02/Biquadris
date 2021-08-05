#include "zblock.h"

ZBlock::ZBlock(std::vector<std::vector<Cell *>> board, int level)
{
	vertical = false;
	SetType('Z');
	SetLevel(level);
	SetPosition(14, 0);
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
	std::vector<Cell *> newCells;
	int size = cells.size();
	for (int i = 0; i < size; i++) {
		cells[i]->SetType('.');
		cells[i]->SetOwner(nullptr);
		if (vertical) {
			newCells.push_back(board[cornerRow][cornerCol + i]);
		} else {
			newCells.push_back(board[cornerRow + i][cornerCol]);
		}
	}
	if (vertical) {
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+2]);
	}
	else {
		newCells.push_back(board[cornerRow+2][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
	}
	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType('Z');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
	vertical = !vertical;
}
