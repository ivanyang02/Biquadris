#include "iblock.h"

IBlock::IBlock(std::vector<std::vector<Cell *>> board, int level, int row, int col)
{
	vertical = false;
	SetType('I');
	SetLevel(level);
	SetPosition(row, col);
	try {
		AddCell(board[row][col]);
		AddCell(board[row][col + 1]);
		AddCell(board[row][col + 2]);
		AddCell(board[row][col + 3]);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void IBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::vector<Cell *> newCells;
	int size = cells.size();
	for (int i = 0; i < size; i++) {
		if (vertical) {
			if (cornerCol + i >= 11) {
				return;
			}
			newCells.push_back(board[cornerRow][cornerCol + i]);
		} else {
			newCells.push_back(board[cornerRow + i][cornerCol]);
		}
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
		newCells[i]->SetType('I');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
	vertical = !vertical;
}
