#include "sblock.h"

SBlock::SBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col)
{
	vertical = false;
	SetType('S');
	SetLevel(level);
	SetPosition(row, col);
	try {
	AddCell(board[row][col].get());
	AddCell(board[row][col + 1].get());
	AddCell(board[row + 1][col + 1].get());
	AddCell(board[row + 1][col + 2].get());
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void SBlock::Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) {
	std::vector <Cell *> newCells;
	int size = cells.size();
	if (vertical) {
		if (cornerCol + 2 >= 11) {
			return;
		}
		newCells.push_back(board[cornerRow][cornerCol].get());
		newCells.push_back(board[cornerRow][cornerCol + 1].get());
		newCells.push_back(board[cornerRow + 1][cornerCol + 1].get());
		newCells.push_back(board[cornerRow + 1][cornerCol + 2].get());
	} else {
		newCells.push_back(board[cornerRow][cornerCol + 1].get());
		newCells.push_back(board[cornerRow + 1][cornerCol + 1].get());
		newCells.push_back(board[cornerRow + 1][cornerCol].get());
		newCells.push_back(board[cornerRow + 2][cornerCol].get());

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
		newCells[i]->SetType('S');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
	vertical = !vertical;
}
