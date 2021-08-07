#include "zblock.h"

ZBlock::ZBlock(std::vector<std::vector<Cell *>> board, int level)
{
	vertical = false;
	SetType('Z');
	SetLevel(level);
	SetPosition(14, 0);
	try {
	AddCell(board[15][0]);
	AddCell(board[15][1]);
	AddCell(board[14][1]);
	AddCell(board[14][2]);
	} catch (OccupiedCell e) {
		throw OccupiedCell{};
	}
}

void ZBlock::Rotate(char direction, std::vector<std::vector<Cell *>> board) {
	std::cout << "zblockrotate " << direction << std::endl;
	std::vector<Cell *> newCells;
	int size = cells.size();
	if (vertical) {
		if (cornerCol + 2 >= 11) {
			return;
		}
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+1]);
		newCells.push_back(board[cornerRow][cornerCol+2]);
	}
	else {
		newCells.push_back(board[cornerRow][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol]);
		newCells.push_back(board[cornerRow+1][cornerCol+1]);
		newCells.push_back(board[cornerRow+2][cornerCol+1]);
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
		newCells[i]->SetType('Z');
		newCells[i]->SetOwner(this);
	}
	cells = newCells;
	vertical = !vertical;
}
