#include "board.h"

Board::Board(int player, Xwindow *w):
	player{player}
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

void Board::AddBlock(char type) {
	if (type == 'I') {
		IBlock *newBlock = new IBlock(board, currentLevel);
		currentBlock = newBlock;
	} else if (type == 'J') {
		JBlock *newBlock = new JBlock(board, currentLevel);
		currentBlock = newBlock;
	} else if (type == 'L') {
		LBlock *newBlock = new LBlock(board, currentLevel);
		currentBlock = newBlock;
	} else if (type == 'O') {
		OBlock *newBlock = new OBlock(board, currentLevel);
		currentBlock = newBlock;
	} else if (type == 'S') {
		SBlock *newBlock = new SBlock(board, currentLevel);
		currentBlock = newBlock;
	} else if (type == 'Z') {
		ZBlock *newBlock = new ZBlock(board, currentLevel);
		currentBlock = newBlock;
	} else if (type == 'T') {
		TBlock *newBlock = new TBlock(board, currentLevel);
		currentBlock = newBlock;
	}
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
		for (int i = 0; i < rows - row - lineCleared; ++i) {
            int up = (i >= (4 - lineCleared) ? lineCleared : movedown[i]);
			for (int j = 0; j < cols; ++j) {
				board[row + i][j]->SetType(board[row + i + up][j]->GetType());
				board[row + i][j]->SetOwner(board[row + i + up][j]->GetOwner());
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

char Board::GetCellType(int row, int col) const {
	return board[row][col]->GetType();
}

int Board::GetRows() const {
	return rows + extra;
}

int Board::GetCols() const {
	return cols;
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
