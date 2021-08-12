#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"
#include "cell.h"

using namespace std;

Xwindow::Xwindow(int width, int height):
	screenWidth{width},
	screenHeight{height}
{
	d = XOpenDisplay(NULL);
	if (d == NULL) {
		cerr << "Cannot open display" << endl;
		exit(1);
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapRaised(d, w);

	Pixmap pix = XCreatePixmap(d,w,width,height,DefaultDepth(d,DefaultScreen(d)));
	gc = XCreateGC(d, pix, 0,(XGCValues *)0);

	XFlush(d);
	XFlush(d);
	XColor xcolour;
	Colormap cmap;
	char color_vals[10][10]={"white", "black", "red", "green", "blue", "orange", "yellow", "purple", "cyan", "brown"};

	cmap=DefaultColormap(d,DefaultScreen(d));
	for(int i=0; i < 10; ++i) {
		XParseColor(d,cmap,color_vals[i],&xcolour);
		XAllocColor(d,cmap,&xcolour);
		colours[i]=xcolour.pixel;
	}
	XSetForeground(d,gc,colours[Black]);
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

	XSynchronize(d,True);

	usleep(1000);

}

Xwindow::~Xwindow() {
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
	XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::SetCellSize(int w, int h) {
	width = w;
	height = h;
}

void Xwindow::SetPlayerOffset(int player, int x, int y) {
	if (player == 1) {
		p1X = x;
		p1Y = y;
	} else {
		p2X = x;
		p2Y = y;
	}
}

void Xwindow::fillCell(int player, int row, int col, char type) {
	if (type == '.') {
		XSetForeground(d, gc, colours[White]);
	} else if (type == 'I') {
		XSetForeground(d, gc, colours[Cyan]);
	} else if (type == 'J') {
		XSetForeground(d, gc, colours[Blue]);
	} else if (type == 'L') {
		XSetForeground(d, gc, colours[Orange]);
	} else if (type == 'O') {
		XSetForeground(d, gc, colours[Yellow]);
	} else if (type == 'S') {
		XSetForeground(d, gc, colours[Green]);
	} else if (type == 'Z') {
		XSetForeground(d, gc, colours[Red]);
	} else if (type == 'T') {
		XSetForeground(d,gc, colours[Purple]);
	}
	int xPosition;
	int yPosition;
	if (player == 1) {
		xPosition = p1X + width * col;
		yPosition = screenHeight - (p1Y + height * row);
	} else {
		xPosition = p2X + width * col;
		yPosition = screenHeight - (p2Y + height * row);

	}
	XFillRectangle(d, w, gc, xPosition, yPosition, width - 1, height - 1);
	XSetForeground(d, gc, colours[Black]);

}

void Xwindow::drawBoard(int rows, int cols, int level1, int level2) {
	fillRectangle(p1X - width, screenHeight - p1Y - rows * height, (cols + 2) * width, (rows + 2) * height, Xwindow::Black);
	fillRectangle(p2X - width, screenHeight - p2Y - rows * height, (cols + 2) * width, (rows + 2) * height, Xwindow::Black);
	drawString(p1X + (cols + 2) * width, screenHeight - (p1Y + (rows - 1) * height), "level:");
	drawString(p1X + (cols + 2) * width, screenHeight - (p1Y + (rows - 3) * height), "score:");
	drawString(p1X + (cols + 2) * width, screenHeight - (p1Y + (rows - 5) * height), "Next:");
    drawString(p1X + (cols + 2) * width, screenHeight - (p1Y + (rows - 10) * height), "Hold:");
	drawString(p2X + (cols + 2) * width, screenHeight - (p2Y + (rows - 1) * height), "level:");
	drawString(p2X + (cols + 2) * width, screenHeight - (p2Y + (rows - 3) * height), "score:");
	drawString(p2X + (cols + 2) * width, screenHeight - (p2Y + (rows - 5) * height), "Next:");
    drawString(p2X + (cols + 2) * width, screenHeight - (p2Y + (rows - 10) * height), "Hold:");

}

void Xwindow::updateBoard(int player, const std::vector<std::vector<Cell *>> &b, int rows, int cols, int score, int level, char next, bool blind, char hold) {
	char data[cols * rows * width * height * 4];
	XImage *newimage = XCreateImage(d, DefaultVisual(d, 0), DefaultDepth(d, 0), ZPixmap, 0, data, cols * width, rows * height, 32, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			for (int k = 0; k < height; k++) {
				for (int l = 0; l < width; l++) {
					int yPos = (rows * height - 1) - (i * height + k);
	if (k == height - 1 || l == width - 1) {
		XPutPixel(newimage, j * width + l, yPos, RGB(200,200,200));
	} else if (blind && i >= 2 && i <= 11 && j >= 2 && j <=8) {
		XPutPixel(newimage, j * width + l, yPos, RGB(50,50,50));
	} else if (b[i][j]->GetType() == '*') {
	XPutPixel(newimage, j * width + l, yPos, colours[Brown]);
	} else if (b[i][j]->GetType() == '.') {
	XPutPixel(newimage, j * width + l, yPos, colours[White]);
	} else if (b[i][j]->GetType() == 'I') {
	XPutPixel(newimage, j * width + l, yPos, colours[Cyan]);
	} else if (b[i][j]->GetType() == 'J') {
	XPutPixel(newimage, j * width + l, yPos, colours[Blue]);
	} else if (b[i][j]->GetType() == 'L') {
	XPutPixel(newimage, j * width + l, yPos, colours[Orange]);
	} else if (b[i][j]->GetType() == 'O') {
	XPutPixel(newimage, j * width + l, yPos, colours[Yellow]);
	} else if (b[i][j]->GetType() == 'S') {
	XPutPixel(newimage, j * width + l, yPos, colours[Green]);
	} else if (b[i][j]->GetType() == 'Z') {
	XPutPixel(newimage, j * width + l, yPos, colours[Red]);
	} else if (b[i][j]->GetType() == 'T') {
	XPutPixel(newimage, j * width + l, yPos, colours[Purple]);
	}
				}
			}
		}
	}
	int x;
	int y;
	if (next != '0') {
		drawBlock(player, next, 11);
	}
	if (hold != '0') {
		drawBlock(player, hold, 6);
	}
	if (player == 1) {
		x = p1X + (cols + 6) * width;
		fillRectangle(x, screenHeight - (p1Y + rows * height), 50, 30, Xwindow::White);
		drawString(x, screenHeight - (p1Y + (rows - 1) * height), std::to_string(level));
		drawString(x, screenHeight - (p1Y + (rows - 3) * height), std::to_string(score));
		XPutImage(d,w,gc, newimage,0,0,p1X,screenHeight - (p1Y + (rows - 1) * height),cols * width, rows * height);
	} else {
		x = p2X + (cols + 6) * width;
		fillRectangle(x, screenHeight - (p2Y + rows * height), 50, 30, Xwindow::White);
		drawString(x, screenHeight - (p2Y + (rows - 1) * height), std::to_string(level));
		drawString(x, screenHeight - (p2Y + (rows - 3) * height), std::to_string(score));
		XPutImage(d,w,gc, newimage,0,0,p2X,screenHeight - (p2Y + (rows - 1) * height),cols * width, rows * height);
	}
}

void Xwindow::drawBlock(int player, char next, int row) {
	if (player == 1) {
		fillRectangle(p1X + 13 * width, screenHeight - (p1Y + (row + 1) * height), 4 * width, 2 * height, Xwindow::White);
	} else {
		fillRectangle(p2X + 13 * width, screenHeight - (p2Y + (row + 1) * height), 4 * width, 2 * height, Xwindow::White);
	}
	if (next == 'I') {
		fillCell(player, row, 13, next);
		fillCell(player, row, 14, next);
		fillCell(player, row, 15, next);
		fillCell(player, row, 16, next);
	} else if (next == 'J') {
		fillCell(player, row + 1, 13, next);
		fillCell(player, row, 13, next);
		fillCell(player, row, 14, next);
		fillCell(player, row, 15, next);
	} else if (next == 'L') {
		fillCell(player, row, 13, next);
		fillCell(player, row, 14, next);
		fillCell(player, row, 15, next);
		fillCell(player, row + 1, 15, next);
	} else if (next == 'O') {
		fillCell(player, row, 13, next);
		fillCell(player, row, 14, next);
		fillCell(player, row + 1, 13, next);
		fillCell(player, row + 1, 14, next);
	} else if (next == 'S') {
		fillCell(player, row, 13, next);
		fillCell(player, row, 14, next);
		fillCell(player, row + 1, 14, next);
		fillCell(player, row + 1, 15, next);
	} else if (next == 'Z') {
		fillCell(player, row + 1, 13, next);
		fillCell(player, row + 1, 14, next);
		fillCell(player, row, 14, next);
		fillCell(player, row, 15, next);
	} else if (next == 'T') {
		fillCell(player, row + 1, 13, next);
		fillCell(player, row + 1, 14, next);
		fillCell(player, row, 14, next);
		fillCell(player, row + 1, 15, next);
	}
}

#include <fstream>
#include <stdlib.h>
void Xwindow::drawPicture(std::string filename, int x, int y) {
	ifstream infile{filename};
	int rows, cols;
	infile >> rows >> cols;
	int r;
	int g;
	int b;
	char data[cols * rows * 4];
	XImage *newimage = XCreateImage(d, DefaultVisual(d, 0), DefaultDepth(d, 0), ZPixmap, 0, data, cols, rows, 32, 0);
	
	unsigned long colorvalue;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			infile >> r >> g >> b;
			colorvalue = RGB(r,g,b);
			XPutPixel(newimage, j, i, colorvalue);
		}
	}
	XPutImage(d, w, gc, newimage, 0, 0, x, y, cols, rows);
}

unsigned long Xwindow::RGB(int r, int g, int b)  {
	return b + (g << 8) + (r << 16);
}
