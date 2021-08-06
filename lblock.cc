#include "lblock.h"

LBlock::LBlock(std::vector<std::vector<Cell *>> board, int level)
{
	position = 0;
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
	std::vector<Cell *> newCells;
	int size = cells.size();
	if (direction == "counterclockwise") {
		position++;
	}
	else {
		position--;
	}
	position = position%4;
	if (position == 3) {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+2]);
		newCells.push_back(board[cornerRow+1][cornerCol+2]);
	}
	if (position == 2) {
		newCells.push_back(board[cornerRow+2][cornerCol]);
		newCells.push_back(board[cornerRow+2][cornerCol+1]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
	}
	if (position == 1) {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+][cornerCol+1]);
		newCells.push_back(board[cornerRow+1][cornerCol+2]);
	}
	else {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+2][cornerCol]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
	}
	for (int i = 0; i < newCells.size(); i++) {
		if (newCells[i]->GetOwner() != nullptr && newCells[i]->GetOwner() != this) {
			return;
		}
	}
	for (int i = 0; i < size; i++) {
		cells[i]->SetType('.');
		cells[i]->SetOwner(nullptr);
	}
	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType('L');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
}
