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
	Cell(int player, int row, int col, Xwindow *w); //Cell constructor
	~Cell(); 					//Cell destructor 
	void AddCell(char t, Block *b);			//Sets the Cell to the given type and block onwer, throws exception if already owned
	void SetType(char t);				//Sets the cell type
	void SetOwner(Block *b);			//Sets the cell owner
	char GetType() const;				//Retrieves the cell type
	Block *GetOwner() const;			//Retrieves the cell owner
	int GetRow();					//Retrieves the cell row
	int GetCol();					//Retrieves the cell column
	bool operator==(const Cell& other);		//Comparator for cells
};

class OccupiedCell {
};

#endif
