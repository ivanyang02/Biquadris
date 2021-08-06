#include "tblock.h"

TBlock::TBlock(std::vector<std::vector<Cell *>> board, int level)
{
	position = 0;
	SetType('T');
	SetLevel(level);
    SetPosition(14, 0);
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
	std::vector<Cell *> newCells;
	int size = cells.size();

    if (position % 2 == 1) {
	    if (cornerCol + 2 >= 11) {
			return;
		}
	}
	if (direction == 'r') {
		position++;
	}
	else {
		position--;
	}

	position = position%4;
	if (position == 3) {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+2][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
	} else if (position == 2) {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+2]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
	} else if (position == 1) {
        newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow+2][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
	} else {
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow+1][cornerCol+2]);
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
		newCells[i]->SetType('T');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
}
