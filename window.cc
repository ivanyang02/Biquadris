#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

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
	char color_vals[7][10]={"white", "black", "red", "green", "blue", "orange"};

	cmap=DefaultColormap(d,DefaultScreen(d));
	for(int i=0; i < 6; ++i) {
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
		XSetForeground(d, gc, colours[Blue]);
	} else if (type == 'J') {
		XSetForeground(d, gc, colours[Orange]);
	} else {
		XSetForeground(d, gc, colours[Green]);
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
	fillRectangle(p1X - width, screenHeight - p1Y - height * (rows - 1), width, height * rows, Xwindow::Black);
	fillRectangle(p1X + cols * width, screenHeight - p1Y - height * (rows - 1), width, height * rows, Xwindow::Black);
	fillRectangle(p1X, screenHeight - (p1Y + rows * height), width * cols, height, Xwindow::Black);
	fillRectangle(p1X, screenHeight - (p1Y - height), width * cols, height, Xwindow::Black);
}


//void Xwindow::updateBoard(const Board &b, int offsetX, int offsetY) {
	//fillRectangle(offsetX, offsetY, width * b.GetCols(), height * b.GetRows(), Xwindow::Green);
//	for (int i = 0; i < b.GetRows(); i++) {
//		for (int j = 0; j < b.GetCols(); j++) {
//			fillCell(j * width + offsetX, (b.GetRows() - i - 1) * height + offsetY, b.GetCellType(i, j));
//		}
//	}
//}
