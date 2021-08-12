#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "board.h"
#include "window.h"

using namespace std;

bool Substring(string a, string b) {
	int len1 = a.length();
	int len2 = b.length();
	if (len1 > len2) {
		return false;
	}
	for (int i = 0; i < len1; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " sequence1 sequence2" << endl;
		return 1;
	}
	vector<string> commands;
	for (int i = 1; i < argc; i++) {
		commands.push_back(argv[i]);
	}

	bool textOnly = false;
	unsigned int seed = 0;
	string cl;
	int defaultlevel = 0;
	bool in1override = false;
	bool in2override = false;
	string input1 = "";
	string input2 = "";
	for (int i = 0; i < argc - 1; i++) {
		cl = commands[i];
		if (cl == "-text") {
			textOnly = true;
		} else if (cl == "-seed") {
			++i;
			seed = stoi(commands[i]);
		} else if (cl == "-scriptfile1") {
			++i;
			input1 = commands[i];
			in1override = true;
		} else if (cl == "-scriptfile2") {
			++i;
			input2 = commands[i];
			in2override = true;
		} else if (cl == "-startlevel") {
			++i;
			defaultlevel = stoi(commands[i]);
		} else {
			if (input1 == "") {
				if (!in1override) {
					input1 = commands[i];
				}
			} else if (!in2override) {
				input2 = commands[i];
			}
		}
	}
	srand(seed);
	ifstream infile1{input1}, infile2{input2};

	Xwindow *w;
	if (!textOnly) {
		w = new Xwindow(500, 500);
		w->SetCellSize(10, 10);
		w->SetPlayerOffset(1, 50, 50);
		w->SetPlayerOffset(2, 280, 50);
		w->drawBoard(18, 11);
		//drawScreen(&w);
		w->drawPicture("splashart.txt", 25,5);
		w->drawPicture("splashart2.txt", 325,5);
	}
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
	Board *b[2];
	b[0] = new Board{1, sequence1, w};
	b[1] = new Board{2, sequence2, w};
	for (int i = 0; i < defaultlevel; i++) {
		b[0]->LevelUp();
		b[1]->LevelUp();
	}
	string command;
	int player = 1;
	b[0]->NewBlock();
	b[0]->NewBlock();
	//b1->AddBlock('S');
	b[1]->NewBlock();
	b[1]->NewBlock();
	if (!textOnly) {
		w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext());
		w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext());
	}
	while(true) {
		if (!textOnly) {
			if (player == 1) {
				w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), '0');
			} else {
				w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), '0');
			}
		}
		if (!(cin >> command)) {
			return 0;
		}
		if (Substring(command, "left") && Substring("lef", command)) {
			b[player - 1]->Move('l');
		} else if (Substring(command, "right") && Substring("ri", command)) {
			b[player - 1]->Move('r');
		} else if (Substring(command, "down") && Substring("do", command)) {
			b[player - 1]->Move('d');
		} else if (Substring(command, "clockwise") && Substring("cl", command)) {
			b[player - 1]->Rotate('r');
		} else if (Substring(command, "counterclockwise") && Substring("co", command)) {
			b[player - 1]->Rotate('l');
		} else if (Substring(command, "drop") && Substring("dr", command)) {
			b[player - 1]->Drop();
			char again;
			if (player == 1) {
				if (!b[0]->NewBlock()) {
					cout << "player 2 wins" << endl;
					cout << "type restart to restart or quit to quit and do not type anything else or i will be sad" << endl;
				}
				if (!textOnly) {
					w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext());
				}
				player = 2;
			} else if (player == 2) {
				if (!b[1]->NewBlock()) {
					cout << "player 1 wins" << endl;
					cout << "type restart to restart or quit to quit and do not type anything else or i will eat your shoes" << endl;
				}
				if (!textOnly) {
					w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext());
				}
				player = 1;
			}
		} else if (Substring(command, "levelup") && Substring("levelu", command)) {
			b[player - 1]->LevelUp();
		} else if (Substring(command, "leveldown") && Substring("leveld", command)) {
			b[player - 1]->LevelDown();
		} else if (Substring(command, "norandom") && Substring("n", command)) {

		} else if (command == "random") {
			srand(seed);
		} else if (command == "sequence") {
			
		} else if (command == "restart") {
			b[0] = new Board{1, sequence1, w};
			b[1] = new Board{2, sequence2, w};
			for (int i = 0; i < defaultlevel; i++) {
				b[0]->LevelUp();
				b[1]->LevelUp();
			}
			player = 1;
			b[0]->NewBlock();
			b[0]->NewBlock();
			//b1->AddBlock('S');
			b[1]->NewBlock();
			b[1]->NewBlock();
			if (!textOnly) {
				w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext());
				w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext());
			}
		} else if (command == "p") {
			cout << b[0] << endl << b[1] << endl;
			//w->updateBoard(b1, 50, 50);
		} else if ( command == "quit") {
			break;
		}
	}
	delete w;
}
