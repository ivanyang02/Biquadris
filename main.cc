#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>

#include "board.h"
#include "window.h"

using namespace std;

// Check for the substring for an input
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

// Returns an array of char indicating how to print the block type t
vector<char> printBlock(char t) {
	if (t == 'I') {
		vector<char> arr{'I', 'I', 'I', 'I', ' ', ' ', ' ', ' '};
		return arr;
	} else if (t == 'J') {
		vector<char> arr{'J', ' ', ' ', ' ', 'J', 'J', 'J', ' '};
		return arr;
	} else if (t == 'L') {
		vector<char> arr{' ', ' ', 'L', ' ', 'L', 'L', 'L', ' '};
		return arr;
	} else if (t == 'S') {
		vector<char> arr{' ', 'S', 'S', ' ', 'S', 'S', ' ', ' '};
		return arr;
	} else if (t == 'Z') {
		vector<char> arr{'Z', 'Z', ' ', ' ', ' ', 'Z', 'Z', ' '};
		return arr;
	} else if (t == 'T') {
		vector<char> arr{'T', 'T', 'T', ' ', ' ', 'T', ' ', ' '};
		return arr;
	} else if (t == 'O') {
		vector<char> arr{'O', 'O', ' ', ' ', 'O', 'O', ' ', ' '};
		return arr;
	} else {
		vector<char> arr{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
		return arr;
	}
}

// Print text display for the game
void printBoard(shared_ptr<Board> *b) {
	// print level and score
	cout << "Level: " << std::setw(4) << b[0]->GetLevel() << "    " << "Level: " << std::setw(4) << b[1]->GetLevel() << endl;
	cout << "Score: " << std::setw(4) << b[0]->GetScore() << "    " << "Score: " << std::setw(4) << b[1]->GetScore() << endl;

	// print the board
	cout << "-----------    -----------" << std::endl;
	for (int i = b[0]->GetRows() - 1; i >= 0; i--) {
	    for (int n = 0; n < 2; ++n) {
			for (int j = 0; j < b[0]->GetCols(); j++) {
				if (b[n]->GetBlind() && i >= 2 && i <= 8 && j >= 2 && j <= 11) {
					cout << '?';
				} else {
					cout << b[n]->GetCellType(i, j);
				}
			}
			cout << "    ";
		}
		cout << endl;
	}
    cout << "-----------    -----------" << endl;

	// print the next block
	cout << "Next:          Next:" << endl;
	for (int i = 0; i < 2; ++i) {
		for (int n = 0; n < 2; ++n) {
            vector<char> block = printBlock(b[n]->GetNext());
			for (int j = 0; j < 4; ++j) {
	            cout << block[i * 4 + j];
			}
			cout << "           ";
		}
		cout << endl;
	}

	// print the hold block
    cout << "Hold:          Hold:" << endl;
	for (int i = 0; i < 2; ++i) {
		for (int n = 0; n < 2; ++n) {
            vector<char> block = printBlock(b[n]->GetHold());
			for (int j = 0; j < 4; ++j) {
	            cout << block[i * 4 + j];
			}
			cout << "           ";
		}
		cout << endl;
	}
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

	// command line interface
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

	// Set up graphics display window
	shared_ptr<Xwindow> w;
	if (!textOnly) {
		w = make_shared<Xwindow>(500, 500);
		w->SetCellSize(10, 10);
		w->SetPlayerOffset(1, 50, 50);
		w->SetPlayerOffset(2, 280, 50);
		w->drawBoard(18, 11);
		//drawScreen(&w);
		w->drawPicture("splashart.txt", 25,5);
		w->drawPicture("splashart2.txt", 325,5);
	}

	// Set up sequence input for players
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

	// Set up the board for players
	shared_ptr<Board> b[2];
	b[0] = make_shared<Board>(1, sequence1, w.get());
	b[1] = make_shared<Board>(2, sequence2, w.get());
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
		w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext(), b[0]->GetBlind(), '0');
		w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext(), b[1]->GetBlind(), '0');
	}
	while (true) {
	while(true) {
		// Display the game
		if (!gg) {
			if (!textOnly) {
				if (player == 1) {
					w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), '0', b[0]->GetBlind(), '0');
				} else {
					w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), '0', b[1]->GetBlind(), '0');
				}
			}
			printBoard(b);
		}
		
		// Get command from cin
		if (command == "heavydrop") {
			command = "drop";
		} else {
			if (!(cin >> command)) {
				return 0;
			}
		}

		if (!gg && Substring(command, "left") && Substring("lef", command)) {
			b[player - 1]->Move('l');
			if (b[player - 1]->HeavyDrop()) {
				command = "heavydrop";
			}
		} else if (!gg && Substring(command, "right") && Substring("ri", command)) {
			b[player - 1]->Move('r');
			if (b[player - 1]->HeavyDrop()) {
				command = "heavydrop";
			}
		} else if (!gg && Substring(command, "down") && Substring("do", command)) {
			b[player - 1]->Move('d');
		} else if (!gg && Substring(command, "clockwise") && Substring("cl", command)) {
			b[player - 1]->Rotate('r');
		} else if (!gg && Substring(command, "counterclockwise") && Substring("co", command)) {
			b[player - 1]->Rotate('l');
		} else if (!gg && command == "hold") {
			b[player - 1]->HoldBlock();
			if (!textOnly) {
				w->updateBoard(player, b[player - 1]->GetBoard(), 18, 11, b[player - 1]->GetScore(), b[player - 1]->GetLevel(), b[player - 1]->GetNext(), b[player - 1]->GetBlind(), b[player - 1]->GetHold());
			}
		} else if (!gg && Substring(command, "drop") && Substring("dr", command)) {
			if (b[player - 1]->Drop()) {
				cout << "Please enter special action" << endl;
				// Special action if multiple lines are cleared
				while ((cin >> command)) {
					if (command == "blind") {
						b[player % 2]->SetBlind();
						break;
					} else if (command == "heavy") {
						b[player % 2]->SetHeavy();
						break;
					} else if (command == "force") {
						char type;
						cin >> type;
						if (type == 'I' || type == 'J' || type == 'L' || type == 'Z' || type == 'S' || type == 'O' || type == 'T') {
							if (!b[player % 2]->ChangeBlock(type)) {
							cout << "player " << player - 1 << " wins" << endl;
							}
							break;
						} else {
							cout << "Invalid type of blocks to force" << endl;
						}
					} else {
						cout << "Invalid special action" << endl;
					}
				}
			}

			// Generate new blocks and game over
			if (player == 1) {
				if (!b[0]->NewBlock()) {
					cout << "player 2 wins" << endl;
					cout << "type restart to restart anything else to quit" << endl;
					break;
				}
				if (!textOnly) {
					w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext(), b[0]->GetBlind(), '0');
				}
				player = 2;
			} else if (player == 2) {
				if (!b[1]->NewBlock()) {
					cout << "player 1 wins" << endl;
					cout << "type restart to restart or anything else to quit" << endl;
					break;
				}
				if (!textOnly) {
					w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext(), b[1]->GetBlind(), '0');
				}
				player = 1;
			}
		} else if (!gg && Substring(command, "levelup") && Substring("levelu", command)) {
			b[player - 1]->LevelUp();
		} else if (!gg && Substring(command, "leveldown") && Substring("leveld", command)) {
			b[player - 1]->LevelDown();
		} else if (Substring(command, "norandom") && Substring("n", command)) {

		} else if (command == "random") {
			srand(seed);
		} else if (command == "sequence") {
			
		} else if (command == "restart") {
			//Board bbb{1, sequence1, w.get()};
			//b[0] = nullptr;
			//b[1] = nullptr;
			//shared_ptr<Board> newBoard1 = make_shared<Board>(1, sequence1, );
			b[0] = make_shared<Board>(1, sequence1, w.get());
			b[1] = make_shared<Board>(2, sequence2, w.get());
			for (int i = 0; i < defaultlevel; i++) {
				b[0]->LevelUp();
				b[1]->LevelUp();
			}
			int player = 1;
			b[0]->NewBlock();
			b[0]->NewBlock();
			//b1->AddBlock('S');
			b[1]->NewBlock();
			b[1]->NewBlock();
			if (!textOnly) {
				w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext(), b[0]->GetBlind(), '0');
				w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext(), b[1]->GetBlind(), '0');
			}
		} else if ( command == "quit") {
			break;
		} else {
			cout << "Invalid Command: " << command <<endl;
			command = "";
		}
	}
	string s;
	cin >> s;
	if (s != "restart") {
		break;
	}
	b[0] = make_shared<Board>(1, sequence1, w.get());
			b[1] = make_shared<Board>(2, sequence2, w.get());
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
				w->updateBoard(1, b[0]->GetBoard(), 18, 11, b[0]->GetScore(), b[0]->GetLevel(), b[0]->GetNext(), b[0]->GetBlind(), b[0]->GetHold());
				w->updateBoard(2, b[1]->GetBoard(), 18, 11, b[1]->GetScore(), b[1]->GetLevel(), b[1]->GetNext(), b[1]->GetBlind(), b[1]->GetHold());
			}

	}
}
