#include <iostream>

#include "block.h"

Block::~Block() {
}

void Block::SetLevel(int lvl) {
	level = lvl;
}

void Block::SetType(char typ) {
	type = typ;
}

void Block::SetPosition(int row, int col) {
	cornerRow = row;
	cornerCol = col;
}

void Block::AddCell(Cell *cell) {
	cells.push_back(cell);
}

bool Block::Move(char direction, std::vector<std::vector<Cell *>> board) {
	std::vector<Cell *> oldCells;
	std::vector<Cell *> sameCells;
	std::vector<Cell *> newCells;
	Cell *current;
	Cell *next;
	int row;
	int col;
	size_t boardcols = board[0].size();
	for (int i = 0; i < cells.size(); i++) {
		current = cells[i];
		row = current->GetRow();
		col = current->GetCol();
		if (direction == 'l') {
			if (col - 1 == -1) {
				return false;
			}
			next = board[row][col - 1];
		} else if (direction == 'r') {
			if (col + 1 == boardcols) {
				return false;
			}
			next = board[row][col + 1];
		} else {
			if (row - 1 < 0) {
				return false;
			}
			next = board[row - 1][col];
		}
		if (current->GetOwner() != next->GetOwner() && next->GetOwner() != nullptr) {
			return false;
		}
		if (current->GetOwner() == next->GetOwner()) {
			sameCells.push_back(next);
		} else {
			newCells.push_back(next);
		}
		oldCells.push_back(current);
	}
	bool same;
	for (int i = 0; i < oldCells.size(); i++) {
		same = false;
		for (int j = 0; j < sameCells.size(); j++) {
			if (oldCells[i] == sameCells[j]) {
				same = true;
				break;
			}
		}
		if (!same) {
			oldCells[i]->SetType('.');
			oldCells[i]->SetOwner(nullptr);
		}
	}
	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType(type);
		newCells[i]->SetOwner(this);
	}
	for (int i = 0; i < sameCells.size(); i++) {
		newCells.push_back(sameCells[i]);
	}
	cells = newCells;
	if (direction == 'l') {
		--cornerCol;
	} else if (direction == 'r') {
		++cornerCol;
	} else {
		--cornerRow;
	}
	return true;
}

//void Block::Rotate(char direction) {
//	std::cout << direction << std::endl;
//}

void Block::Drop(std::vector<std::vector<Cell *>> board) {
	while (Move('d', board));
}
