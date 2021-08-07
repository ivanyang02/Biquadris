#include "cell.h"
#include "block.h"

Cell::Cell(int player, int row, int col, Xwindow *w):
	player{player},
	row{row},
	col{col},
	type{'.'},
	owner{nullptr},
	window{w}
{}

Cell::~Cell() {
}

void Cell::AddCell(char t, Block *owner) {
	if (GetOwner() != nullptr) {
		throw OccupiedCell{};
	}
	SetType(t);
	SetOwner(owner);
}

void Cell::SetType(char t) {
	type = t;
	if (window != nullptr) {
	//	window->fillCell(player, row, col, type);
	}
}

void Cell::SetOwner(Block *b) {
	owner = b;
}

char Cell::GetType() const {
	return type;
}

Block *Cell::GetOwner() const {
	return owner;
}

int Cell::GetRow() {
	return row;
}

int Cell::GetCol() {
	return col;
}

bool Cell::operator==(const Cell &other) {
	if (player != other.player) {
		return false;
	}
	if (row != other.row) {
		return false;
	}
	if (col != other.col) {
		return false;
	}
	if (type != other.type) {
		return false;
	}
	if (owner != other.owner) {
		return false;
	}
	return true;
}

//OccupiedCell::OccupiedCell() {}
