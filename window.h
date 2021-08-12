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
	Xwindow(int width, int height);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.
	
	enum {White=0, Black, Red, Green, Blue, Orange, Yellow, Purple, Cyan, Brown}; // Available colours.

	void fillRectangle(int x, int y, int width, int height, int colour=Black); // Draws a rectangle at location x,y with size width and height with a default colour Black
	void drawString(int x, int y, std::string msg);  // Draws a string at location x,y
	
	void SetCellSize(int width, int height); //Sets cell's width and height
	void SetPlayerOffset(int player, int x, int y); //Sets the offset between the two player boards
	void fillCell(int player, int x, int y, char type); // Draws a cell
	void drawBoard(int rows, int cols, int level1 = 0, int level2 = 0); // Draws the board outline
	void updateBoard(int player, const std::vector<std::vector<Cell *>> &b, int rows, int cols, int score, int level, char next, bool blind); // redraws the content of the board
	void drawNext(int player, char type); // draws the next block
	void drawPicture(std::string filename, int x, int y); // draws a picture
	unsigned long RGB(int r, int g, int b); // converts 3 integers into a long for rgb value
};

#endif
