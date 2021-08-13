#include "iblock.h"

IBlock::IBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col, int id)
{
	vertical = false;
	SetType('I');
	SetLevel(level);
	SetPosition(row, col);
	try {
		AddCell(board[row][col].get(), id);
		AddCell(board[row][col + 1].get(), id);
		AddCell(board[row][col + 2].get(), id);
		AddCell(board[row][col + 3].get(), id);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
	SetOwner(id);
}

void IBlock::Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) {
	std::vector<Cell *> newCells;
	int size = cells.size();
	for (int i = 0; i < size; i++) {
		if (vertical) {
			if (cornerCol + i >= 11) {
				return;
			}
			newCells.push_back(board[cornerRow][cornerCol + i].get());
		} else {
			newCells.push_back(board[cornerRow + i][cornerCol].get());
		}
	}
	for (int i = 0; i < newCells.size(); i++) {
		if (newCells[i]->GetOwner() != -1 && newCells[i]->GetOwner() != id) {
			return;
		}
	}
	RemoveAll();
	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType('I');
		newCells[i]->SetOwner(id);
	}
	cells = newCells;
	vertical = !vertical;
}
