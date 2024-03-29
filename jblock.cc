#include "jblock.h"

JBlock::JBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col, int id)
{
	position = 0;
	SetType('J');
	SetLevel(level);
	SetPosition(row, col);
	try {
	AddCell(board[row + 1][col].get(), id);
	AddCell(board[row][col].get(), id);
	AddCell(board[row][col + 1].get(), id);
	AddCell(board[row][col + 2].get(), id);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
	SetOwner(id);
}

void JBlock::Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) {
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
		newCells.push_back(board[cornerRow][cornerCol].get());
		newCells.push_back(board[cornerRow][cornerCol+1].get());
		newCells.push_back(board[cornerRow+1][cornerCol+1].get());
		newCells.push_back(board[cornerRow+2][cornerCol+1].get());
	} else if (position == 2) {
		newCells.push_back(board[cornerRow+1][cornerCol].get());
		newCells.push_back(board[cornerRow+1][cornerCol+1].get());
		newCells.push_back(board[cornerRow+1][cornerCol+2].get());
		newCells.push_back(board[cornerRow][cornerCol+2].get());
	} else if (position == 1) {
		newCells.push_back(board[cornerRow][cornerCol].get());
		newCells.push_back(board[cornerRow+1][cornerCol].get());
		newCells.push_back(board[cornerRow+2][cornerCol].get());
		newCells.push_back(board[cornerRow+2][cornerCol+1].get());
	} else {
		newCells.push_back(board[cornerRow][cornerCol].get());
		newCells.push_back(board[cornerRow+1][cornerCol].get());
		newCells.push_back(board[cornerRow][cornerCol+1].get());
		newCells.push_back(board[cornerRow][cornerCol+2].get());
	}

	for (int i = 0; i < newCells.size(); i++) {
		if (newCells[i]->GetOwner() != -1 && newCells[i]->GetOwner() != id) {
			position = oldposition;
			return;
		}
	}
	
	RemoveAll();

	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType('J');
		newCells[i]->SetOwner(id);
	}
	cells = newCells;
}
