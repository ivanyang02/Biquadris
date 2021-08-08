#include "board.h"
#include <cstdlib>

Board::Board(int player, std::vector<char> seq, Xwindow *w):
	player{player},
	sequence{seq}
{
	board = std::vector<std::vector<std::shared_ptr<Cell>>>(rows + extra);
	for (int i = 0; i < rows + extra; i++) {
		board[i] = std::vector<std::shared_ptr<Cell>>(cols);
		for (int j = 0; j < cols; j++) {
			board[i][j] = std::make_shared<Cell>(player, i, j, w);
		}
	}
}

Board::~Board() {
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
	if (!AddBlock(type)) return false;
	return true;
}

bool Board::AddBlock(char type) {
	std::shared_ptr<Block> newBlock;
	try {
		if (nextBlock == 'I') {
			std::shared_ptr<IBlock> temp = std::make_shared<IBlock>(board, currentLevel);
			newBlock = temp;
		} else if (nextBlock == 'J') {
			std::shared_ptr<JBlock> temp = std::make_shared<JBlock>(board, currentLevel);
			newBlock = temp;
		} else if (nextBlock == 'L') {
			std::shared_ptr<LBlock> temp = std::make_shared<LBlock>(board, currentLevel);
			newBlock = temp;
		} else if (nextBlock == 'O') {
			std::shared_ptr<OBlock> temp = std::make_shared<OBlock>(board, currentLevel);
			newBlock = temp;
		} else if (nextBlock == 'S') {
			std::shared_ptr<SBlock> temp = std::make_shared<SBlock>(board, currentLevel);
			newBlock = temp;
		} else if (nextBlock == 'Z') {
			std::shared_ptr<ZBlock> temp = std::make_shared<ZBlock>(board, currentLevel);
			newBlock = temp;
		} else if (nextBlock == 'T') {
			std::shared_ptr<TBlock> temp = std::make_shared<TBlock>(board, currentLevel);
			newBlock = temp;
		}
	} catch (OccupiedCell e) {
		std::cout << "false" << std::endl;
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
	if (currentLevel < 4) ++currentLevel;
}

void Board::LevelDown() {
	if (currentLevel > 0) --currentLevel;
}

std::vector<std::vector<std::shared_ptr<Cell>>> Board::GetBoard() const {
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

std::ostream &operator<<(std::ostream &out, const Board &b) {
	for (int i = b.rows + b.extra - 1; i >= 0; i--) {
		for (int j = 0; j < b.cols; j++) {
			std::cout << b.GetCellType(i, j);
		}
		std:: cout << std::endl;
	}
	return out;
}
