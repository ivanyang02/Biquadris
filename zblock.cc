#include "zblock.h"

ZBlock::ZBlock(std::vector<std::vector<std::shared_ptr<Cell>>> board, int level, int row, int col, int id)
{
	vertical = false;
	SetType('Z');
	SetLevel(level);
	SetPosition(row, col);
	try {
	AddCell(board[row + 1][col].get(), id);
	AddCell(board[row + 1][col + 1].get(), id);
	AddCell(board[row][col + 1].get(), id);
	AddCell(board[row][col + 2].get(), id);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void ZBlock::Rotate(char direction, std::vector<std::vector<std::shared_ptr<Cell>>> board) {
	std::vector<Cell *> newCells;
	int size = cells.size();
	if (vertical) {
		if (cornerCol + 2 >= 11) {
			return;
		}
		newCells.push_back(board[cornerRow+1][cornerCol].get());
		newCells.push_back(board[cornerRow+1][cornerCol+1].get());
		newCells.push_back(board[cornerRow][cornerCol+1].get());
		newCells.push_back(board[cornerRow][cornerCol+2].get());
	}
	else {
		newCells.push_back(board[cornerRow][cornerCol].get());
		newCells.push_back(board[cornerRow+1][cornerCol].get());
		newCells.push_back(board[cornerRow+1][cornerCol+1].get());
		newCells.push_back(board[cornerRow+2][cornerCol+1].get());
	}
	for (int i = 0; i < newCells.size(); i++) {
		if (newCells[i]->GetOwner() != -1 && newCells[i]->GetOwner() != id) {
			return;
		}
	}
	RemoveAll();
	for (int i = 0; i < newCells.size(); i++) {
		newCells[i]->SetType('Z');
		newCells[i]->SetOwner(id);
	}
	cells = newCells;
	vertical = !vertical;
}
