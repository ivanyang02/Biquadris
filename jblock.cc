#include "jblock.h"

JBlock::JBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col)
{
	position = 0;
	SetType('J');
	SetLevel(level);
	SetPosition(row, col);
	try {
	AddCell(board[row + 1][col]);
	AddCell(board[row][col]);
	AddCell(board[row][col + 1]);
	AddCell(board[row][col + 2]);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void JBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::vector<Cell *> newCells;
	int size = cells.size();
	int oldposition = position;
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

	if (position < 0) {
		position = 3;
	}
	if (position > 3) {
		position = 0;
	}
	if (position == 3) {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow+2][cornerCol+1]);
	} else if (position == 2) {
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow+1][cornerCol+2]);
		newCells.push_back(board[cornerRow][cornerCol+2]);
	} else if (position == 1) {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+2][cornerCol]);
		newCells.push_back(board[cornerRow+2][cornerCol+1]);
	} else {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+2]);
	}

	for (int i = 0; i < newCells.size(); i++) {
		if (newCells[i]->GetOwner() != nullptr && newCells[i]->GetOwner() != this) {
			position = oldposition;
			return;
		}
	}

	for (int i = 0; i < size; i++) {
		cells[i]->SetType('.');
		cells[i]->SetOwner(nullptr);
	}

	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType('J');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
}
