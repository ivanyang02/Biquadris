#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "board.h"
#include "window.h"

using namespace std;

void drawScreen(Xwindow *w) {
	int player2offset = 200;

	w->drawString(50,50,"Level:    0");
	w->drawString(50 + player2offset,50,"Level:    0");
	
	for (int i = 0; i < 16; i++) {
		if (i % 2 == 1) {
			w->fillRectangle(50, 100 + 10 * i, 10, 10, Xwindow::Black);
			w->fillRectangle(170, 100 + 10 * i, 10, 10, Xwindow::Black);
		} else {
			w->fillRectangle(50, 100 + 10 * i, 10, 10, Xwindow::Blue);
			w->fillRectangle(170, 100 + 10 * i, 10, 10, Xwindow::Blue);
		}
	}
	for (int i = 0; i < 13; i++) {
		if (i % 2 == 1) {
			w->fillRectangle(50 + 10 * i, 100 + 10 * 16, 10, 10, Xwindow::Black);
		}
		if (i % 2 == 0) {
			w->fillRectangle(50 + 10 * i, 100 + 10 * 16, 10, 10, Xwindow::Blue);
		}
	}
	for (int i = 0; i < 16; i++) {
		if (i % 2 == 1) {
			w->fillRectangle(50 + player2offset, 100 + 10 * i, 10, 10, Xwindow::Black);
			w->fillRectangle(170 + player2offset, 100 + 10 * i, 10, 10, Xwindow::Black);
		} else {
			w->fillRectangle(50 + player2offset, 100 + 10 * i, 10, 10, Xwindow::Blue);
			w->fillRectangle(170 + player2offset, 100 + 10 * i, 10, 10, Xwindow::Blue);
		}
	}
	for (int i = 0; i < 13; i++) {
		if (i % 2 == 1) {
			w->fillRectangle(50 + 10 * i + player2offset, 100 + 10 * 16, 10, 10, Xwindow::Black);
		}
		if (i % 2 == 0) {
			w->fillRectangle(50 + 10 * i + player2offset, 100 + 10 * 16, 10, 10, Xwindow::Blue);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " sequence1 sequence2" << endl;
		return 1;
	}
	Xwindow w;
	w.SetCellSize(10, 10);
	w.SetPlayerOffset(1, 50, 50);
	w.SetPlayerOffset(2, 280, 50);
	w.drawBoard(18, 11);
	//drawScreen(&w);
	w.drawPicture("splashart.txt", 25,5);
	w.drawPicture("splashart2.txt", 325,5);
	string input1 = argv[1], input2 = argv[2];
	ifstream infile1{input1}, infile2{input2};
	vector<char> sequence1, sequence2;
	char block1, block2;
	int level1 = 0, level2 = 0;
	size_t blockIndex1 = 1, blockIndex2 = 1;
	while(infile1 >> block1) {
		sequence1.push_back(block1);
	}
	while(infile2 >> block2) {
		sequence2.push_back(block2);
	}

	Board b[2] = {Board{1, sequence1, &w}, Board{2, sequence2, &w}};
	string command;
	int player = 1;
	b[0].NewBlock();
	b[0].NewBlock();
	//b1.AddBlock('S');
	b[1].NewBlock();
	b[1].NewBlock();
	w.updateBoard(1, b[0].GetBoard(), 18, 11, b[0].GetScore(), b[0].GetLevel(), b[0].GetNext());
	while(true) {
		if (player == 2) {
			w.updateBoard(1, b[0].GetBoard(), 18, 11, b[0].GetScore(), b[0].GetLevel(), b[0].GetNext());
		} else {
			w.updateBoard(2, b[1].GetBoard(), 18, 11, b[1].GetScore(), b[1].GetLevel(), b[1].GetNext());
		}
		if (!(cin >> command)) {
			return 0;
		}
		if (command == "left") {
			b[player - 1].Move('l');
		} else if (command == "right") {
			b[player - 1].Move('r');
		} else if (command == "down") {
			b[player - 1].Move('d');
		} else if (command == "clockwise") {
			b[player - 1].Rotate('r');
		} else if (command == "counterclockwise") {
			b[player - 1].Rotate('l');
		} else if (command == "drop") {
			b[player - 1].Drop();
			if (player == 1) {
				if (!b[0].NewBlock()) {
					cout << "player 2 wins" << endl;
					break;
				}
				//w.updateBoard(1, b[0].GetBoard(), 18, 11, b[0].GetScore(), b[0].GetLevel(), b[0].GetNext());
				player = 2;
			} else if (player == 2) {
				if (!b[1].NewBlock()) {
					cout << "player 1 wins" << endl;
					break;
				}
				//w.updateBoard(2, b[1].GetBoard(), 18, 11, b[1].GetScore(), b[1].GetLevel(), b[1].GetNext());
				player = 1;
			}
		} else if (command == "levelup") {
			b[player - 1].LevelUp();
		} else if (command == "leveldown") {
			b[player - 1].LevelDown();
		} else if (command == "norandom") {

		} else if (command == "random") {

		} else if (command == "sequence") {
		
		} else if (command == "restart") {
		
		} else if (command == "p") {
			cout << b[0] << endl << b[1] << endl;
			//w.updateBoard(b1, 50, 50);
		}
	}
}
