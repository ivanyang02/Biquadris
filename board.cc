#include "board.h"
#include <cstdlib>

Board::Board(int player, std::vector<char> seq, Xwindow *w):
	player{player},
	sequence{seq}
{
	board = std::vector<std::vector<Cell *>>(rows + extra);
	for (int i = 0; i < rows + extra; i++) {
		board[i] = std::vector<Cell *>(cols);
		for (int j = 0; j < cols; j++) {
			board[i][j] = new Cell(player, i, j, w);
			board[i][j]->SetOwner(nullptr);
			board[i][j]->SetType('.');
		}
	}
}

Board::~Board() {
	std::vector<Block *> blocks;
	for (int i = 0; i < rows + extra; i++) {
		for (int j = 0; j < cols; j++) {
			blocks.push_back(board[i][j]->GetOwner());
			delete board[i][j];
		}
		board[i].clear();
	}
	board.clear();
	int size = blocks.size();
	for (int i = 0; i < size; i++) {
		delete blocks[i];
	}
}

bool Board::NewBlock() {
	char type;
	if (currentLevel == 0) {
		type = sequence[seqIndex];
		++seqIndex;
		if (seqIndex == sequence.size()) {
			seqIndex = 0;
		}
	} else if (currentLevel == 1) {
		char blocks[12] = {'I', 'I', 'J', 'J', 'L', 'L', 'O', 'O', 'T', 'T', 'S', 'Z'};
		int rng = rand() % 12;
		type = blocks[rng];
	} else if (currentLevel == 2) {
		char blocks[7] = {'I', 'J', 'L', 'O', 'T', 'S', 'Z'};
		int rng = rand() % 7;
		type = blocks[rng];
	} else {
		char blocks[9] = {'I', 'J', 'L', 'O', 'T', 'S', 'S', 'Z', 'Z'};
		int rng = rand() % 9;
		type = blocks[rng];
	}
	if (currentLevel == 4) {
		if (level4Count % 5 == 0) {
		   bool toohigh = true;
			for (int i = 0; i < rows; ++i) {
				if (board[i][5]->GetType() == '.') {
					board[i][5]->SetType('*');
					toohigh = false;
					ClearLine(i);
					break;
				}
			}
			if (toohigh) return false;
		}
	}
	if (!AddBlock(type, 14, 0)) return false;
	return true;
}

bool Board::AddBlock(char type, int row, int col) {
	Block *newBlock;
	try {
		if (nextBlock == 'I') {
			IBlock *temp = new IBlock(board, currentLevel, row, col);
			newBlock = temp;
		} else if (nextBlock == 'J') {
			JBlock *temp = new JBlock(board, currentLevel, row, col);
			newBlock = temp;
		} else if (nextBlock == 'L') {
			LBlock *temp = new LBlock(board, currentLevel, row, col);
			newBlock = temp;
		} else if (nextBlock == 'O') {
			OBlock *temp = new OBlock(board, currentLevel, row, col);
			newBlock = temp;
		} else if (nextBlock == 'S') {
			SBlock *temp = new SBlock(board, currentLevel, row, col);
			newBlock = temp;
		} else if (nextBlock == 'Z') {
			ZBlock *temp = new ZBlock(board, currentLevel, row, col);
			newBlock = temp;
		} else if (nextBlock == 'T') {
			TBlock *temp = new TBlock(board, currentLevel, row, col);
			newBlock = temp;
		}
	} catch (OccupiedCell e) {
		return false;
	}
	currentBlock = newBlock;
	nextBlock = type;
	return true;
}

void Board::Move(char direction) {
	//std::cout << "nerf ganyu";
	currentBlock->Move(direction, board);
	//std::cout << "nerf venti";
}

void Board::Rotate(char direction) {
	currentBlock->Rotate(direction, board);
}

bool Board::Drop() {
	if (blind) blind = false;
	if (heavy) heavy = false;
	currentBlock->Drop(board);
	if (currentLevel == 4) ++level4Count;
	if (ClearLine(currentBlock->GetCoRow()) >= 2) {
		return true;
	}
	return false;
}

bool Board::HeavyDrop() {
	if (heavy) {
		int r = currentBlock->GetCoRow();
		currentBlock->Move('d', board);
        currentBlock->Move('d', board);
		if (r - 2 < currentBlock->GetCoRow()) {
		   return true;
		}
	}
	return false;
}

int Board::ClearLine(int row) {
	std::vector<int> lines;
	bool full;
	for (int i = 0; i < 4; i++) {
		full = true;
		for (int j = 0; j < cols; j++) {
			if (board[row + i][j]->GetType() == '.') {
				full = false;
				break;
			}
		}
		if (full) {
			lines.push_back(i);
		}
	}
	int size = lines.size();
	if (size > 0) {
		score += (size + currentLevel) * (size + currentLevel);
	}
	bool linetoclear;
	int up = 0;
		for (int i = 0; i < 4; i++) {
			linetoclear = false;
			for (int j = 0; j < size; j++) {
				if (lines[j] == i) {
					linetoclear = true;
				}
			}
			if (linetoclear) {
				for (int j = 0; j < cols; j++) {
					Block *current = board[row + up][j]->GetOwner();
					if (current != nullptr) {
						current->RemoveCell(board[row + up][j]);
						if (current->GetCellsCount() == 0) {
							score += (current->GetLevel() + 1) * (current->GetLevel() + 1);
							delete current;
						}
					}
					board[row + up][j]->SetType('.');
					
				}
				for (int j = row + 1 + up; j < rows; j++) {
					for (int k = 0; k < cols; k++) {
						Block *current = board[j][k]->GetOwner();
						if (current != nullptr) {
							current->RemoveCell(board[j][k]);
							current->AddCell(board[j - 1][k]);
						} else if (board[j][k]->GetType() == '*') {
							board[j][k]->SetType('.');
							board[j - 1][k] ->SetType('*');
						}
					}
				}
			} else {
				up++;
			}
		}
	return lines.size();
}

void Board::LevelUp() {
	if (currentLevel < 4) ++currentLevel;
}

void Board::LevelDown() {
	if (currentLevel > 0) --currentLevel;
}

std::vector<std::vector<Cell *>> Board::GetBoard() const {
	return board;
}

char Board::GetCellType(int row, int col) const {
	return board[row][col]->GetType();
}

int Board::GetRows() const {
	return rows + extra;
}

int Board::GetCols() const {
	return cols;
}

int Board::GetLevel() const{
	return currentLevel;
}

int Board::GetScore() const {
	return score;
}

char Board::GetNext() const {
	return nextBlock;
}

bool Board::GetBlind() const {
	return blind;
}

void Board::SetBlind() {
	blind = true;
}

void Board::SetHeavy() {
	heavy = true;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
	for (int i = b.rows + b.extra - 1; i >= 0; i--) {
		for (int j = 0; j < b.cols; j++) {
			std::cout << b.GetCellType(i, j);
		}
		std:: cout << std::endl;
	}
	return out;
}
