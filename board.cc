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
		}
	}
}

Board::~Board() {
	for (int i = 0; i < rows + extra; i++) {
		for (int j = 0; j < cols; j++) {
			delete board[i][j];
		}
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
					break;
				}
			}
			if (toohigh) return false;
		}
	}
	if (!AddBlock(type)) return false;
	return true;
}

bool Board::AddBlock(char type) {
	Block *newBlock;
	try {
		if (type == 'I') {
			IBlock *temp = new IBlock(board, currentLevel);
			newBlock = temp;
		} else if (type == 'J') {
			JBlock *temp = new JBlock(board, currentLevel);
			newBlock = temp;
		} else if (type == 'L') {
			LBlock *temp = new LBlock(board, currentLevel);
			newBlock = temp;
		} else if (type == 'O') {
			OBlock *temp = new OBlock(board, currentLevel);
			newBlock = temp;
		} else if (type == 'S') {
			SBlock *temp = new SBlock(board, currentLevel);
			newBlock = temp;
		} else if (type == 'Z') {
			ZBlock *temp = new ZBlock(board, currentLevel);
			newBlock = temp;
		} else if (type == 'T') {
			TBlock *temp = new TBlock(board, currentLevel);
			newBlock = temp;
		}
	} catch (OccupiedCell e) {
		std::cout << "false" << std::endl;
		return false;
	}
	currentBlock = newBlock;
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

void Board::Drop() {
	currentBlock->Drop(board);
	ClearLine(currentBlock->GetCoRow());
	if (currentLevel == 4) ++level4Count;
}

void Board::ClearLine(int row) {
	int lineCleared = 0;
	int count = 0;
	int movedown[4] = {0};
	for (int i = 0; i < 4; ++i) {
		int clear = 1;
		for (int j = 0; j < cols; ++j) {
			if (board[row + i][j]->GetType() == '.') {
				clear = 0;
				movedown[count] = i - count;
				++count;
				break;
			}
		}
		lineCleared += clear;
	}

	if (lineCleared > 0) {
		score += (lineCleared + currentLevel) * (lineCleared + currentLevel);
		for (int i = 0; i < rows - row - lineCleared; ++i) {
			int up = (i >= (4 - lineCleared) ? lineCleared : movedown[i]);
			for (int j = 0; j < cols; ++j) {
				if (board[row + i][j]->GetType() != '.' || board[row + i + up][j]->GetType() != '.') {
					Block *curOwner = board[row + i][j]->GetOwner();
					Block *newOwner = board[row + i + up][j]->GetOwner();
					if (curOwner != nullptr) {
						curOwner->RemoveCell(board[row + i][j]);
					} else {
						board[row + i][j]->SetType('.');
					}
					if (newOwner != nullptr) {
						newOwner->RemoveCell(board[row + i + up][j]);
						newOwner->AddCell(board[row + i][j]);
					} else if (board[row + i + up][j]->GetType() == '*') {
						board[row + i + up][j]->SetType('.');
						board[row + i][j]->SetType('*');
					}
					if (curOwner != nullptr && curOwner->GetCellsCount() == 0) {
						score += (curOwner->GetLevel() + 1) * (curOwner->GetLevel() + 1);
					}
				}
			}
		}
	    for (int i = rows - lineCleared; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				board[i][j]->SetType('.');
				board[i][j]->SetOwner(nullptr);
			}
		}
	}
}

void Board::LevelUp() {
	if (currentLevel >= 4) return;
	++currentLevel;
}

void Board::LevelDown() {
	if (currentLevel <= 0) return;
	--currentLevel;
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

std::ostream &operator<<(std::ostream &out, const Board &b) {
	for (int i = b.rows + b.extra - 1; i >= 0; i--) {
		for (int j = 0; j < b.cols; j++) {
			std::cout << b.GetCellType(i, j);
		}
		std:: cout << std::endl;
	}
	return out;
}
