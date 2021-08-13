#include <iostream>

#include "block.h"

Block::~Block() {
}

char Block::GetType() {
	return type;
}

int Block::GetLevel() {
	return level;
}

int Block::GetCoRow() {
	return cornerRow;
}

int Block::GetCoCol() {
	return cornerCol;
}

int Block::GetCellsCount() {
	return cells.size();
}

void Block::SetLevel(int lvl) {
	level = lvl;
}

void Block::SetType(char typ) {
	type = typ;
}

void Block::SetOwner(int ownerId) {
	id = ownerId;
}

void Block::SetPosition(int row, int col) {
	cornerRow = row;
	cornerCol = col;
}

void Block::AddCell(Cell *cell, int ownerId) {
	cell->AddCell(type, ownerId);
	cells.push_back(cell);
}

void Block::RemoveCell(Cell *cell) {
	cell->SetType('.');
	cell->SetOwner(-1);
	for (int i = 0; i < cells.size(); ++i) {
		if (cells[i] = cell) {
			cells.erase(cells.begin() + i);
			break;
		}
	}
}

void Block::RemoveAll() {
	int len = cells.size();
	for (int i = len - 1; i >= 0; --i) {
		cells[i]->SetType('.');
		cells[i]->SetOwner(-1);
		cells.pop_back();
	}
}

bool Block::Move(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) {
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
			next = board[row][col - 1].get();
		} else if (direction == 'r') {
			if (col + 1 == boardcols) {
				return false;
			}
			next = board[row][col + 1].get();
		} else {
			if (row - 1 < 0) {
				return false;
			}
			next = board[row - 1][col].get();
		}
		bool same = false;
		for (int j = 0; j < cells.size(); j++) {
			if (next == cells[j]) {
				same = true;
				newCells.push_back(next);
				break;
			}
		}
		if (!same) {
			if (next->GetType() != '.') {
				return false;
			} else {
				newCells.push_back(next);
			}
		}
	}

	RemoveAll();
	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType(type);
		newCells[i]->SetOwner(id);
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

void Block::Drop(std::vector<std::vector<std::shared_ptr<Cell>>> board) {
	while (Move('d', board));
}
