#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>

//#include "cell.h"
//#include "board.h"

class Cell;

class Xwindow {
	Display *d;
	Window w;
	int s;
	
	int screenWidth;
	int screenHeight;
	int width;
	int height;
	int p1X;
	int p1Y;
	int p2X;
	int p2Y;

	GC gc;
	unsigned long colours[10];

	public:
	Xwindow(int width=500, int height=500);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.

	enum {White=0, Black, Red, Green, Blue, Orange, Yellow, Purple, Cyan}; // Available colours.

	void fillRectangle(int x, int y, int width, int height, int colour=Black);
	void drawString(int x, int y, std::string msg);
	
	void SetCellSize(int width, int height);
	void SetPlayerOffset(int player, int x, int y);
	void fillCell(int player, int x, int y, char type);
	void drawBoard(int rows, int cols, int level1 = 0, int level2 = 0);
	void updateBoard(const std::vector<std::vector<Cell *>> &b, int rows, int cols);
	void drawPicture();
	unsigned long RGB(int r, int g, int b);
};

#endif
