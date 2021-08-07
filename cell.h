#ifndef _CELL_H_
#define _CELL_H_

#include "window.h"

class Block;

class Cell {
	int player;
	int row;
	int col;
	char type;
	Block *owner;
	Xwindow *window;
	public:
	Cell(int player, int row, int col, Xwindow *w);
	~Cell();
	void AddCell(char t, Block *b);
	void SetType(char t);
	void SetOwner(Block *b);
	char GetType() const;
	Block *GetOwner() const;
	int GetRow();
	int GetCol();
	bool operator==(const Cell& other);
};

class OccupiedCell {
};

#endif
