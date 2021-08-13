#include "board.h"
#include <cstdlib>

Board::Board(int player, std::vector<char> seq, Xwindow *w):
	player{player},
	sequence{seq}
{
	blocks = std::vector<std::shared_ptr<Block>>(200);
	board = std::vector<std::vector<std::shared_ptr<Cell>>>(rows + extra);
	for (int i = 0; i < rows + extra; i++) {
		board[i] = std::vector<std::shared_ptr<Cell>>(cols);
		for (int j = 0; j < cols; j++) {
			board[i][j] = std::make_shared<Cell>(player, i, j, w);
		}
	}
}

Board::~Board() {
	return;
	for (int i = 0; i < rows + extra; i++) {
		for (int j = 0; j < cols; j++) {
			blocks[board[i][j]->GetOwner()]->RemoveAll();
		}
		board[i].clear();
	}
	board.clear();
	blocks.clear();
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
	if (AddBlock(nextBlock, 14, 0)) {
		nextBlock = type;
	 	return true;
	}
	return false;
}

bool Board::AddBlock(char type, int row, int col) {
	std::shared_ptr<Block> newBlock;
	for (int i = 0; i < 200; i++) {
		if (blocks[i] == nullptr) {
			currentIdx = i;
			break;
		}
	}
	try {
		if (type == 'I') {
			std::shared_ptr<IBlock> temp = std::make_shared<IBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		} else if (type == 'J') {
			std::shared_ptr<JBlock> temp = std::make_shared<JBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		} else if (type == 'L') {
			std::shared_ptr<LBlock> temp = std::make_shared<LBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		} else if (type == 'O') {
			std::shared_ptr<OBlock> temp = std::make_shared<OBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		} else if (type == 'S') {
			std::shared_ptr<SBlock> temp = std::make_shared<SBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		} else if (type == 'Z') {
			std::shared_ptr<ZBlock> temp = std::make_shared<ZBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		} else if (type == 'T') {
			std::shared_ptr<TBlock> temp = std::make_shared<TBlock>(board, currentLevel, row, col, currentIdx);
			newBlock = temp;
		}
	} catch (OccupiedCell e) {
		return false;
	}
	blocks[currentIdx] = newBlock;
	return true;
}

bool Board::ChangeBlock(char type) {
	std::shared_ptr<Block> currentBlock = blocks[currentIdx];
	int r = currentBlock->GetCoRow();
	int c = currentBlock->GetCoCol();
	currentBlock->RemoveAll();
	if (AddBlock(type, r, c)) return true;
	return false;
}

void Board::Move(char direction) {
	std::shared_ptr<Block> currentBlock = blocks[currentIdx];
	currentBlock->Move(direction, board);
	if (currentBlock->GetLevel() >= 3) {
		currentBlock->Move('d', board);
	}
	//std::cout << "nerf venti";
}

void Board::Rotate(char direction) {
	std::shared_ptr<Block> currentBlock = blocks[currentIdx];
	currentBlock->Rotate(direction, board);
	if (currentBlock->GetLevel() >= 3) {
		currentBlock->Move('d', board);
	}
}

void Board::HoldBlock() {
	std::shared_ptr<Block> currentBlock = blocks[currentIdx];
	if (hold == '0') {
		hold = currentBlock->GetType();
        currentBlock->RemoveAll();
        NewBlock();
	} else {
		char type = currentBlock->GetType();
		currentBlock->RemoveAll();
		AddBlock(hold, 14, 0);
		hold = type;
	}
	std::cout << hold << std::endl;
}

bool Board::Drop() {
	std::shared_ptr<Block> currentBlock = blocks[currentIdx];
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
	std::shared_ptr<Block> currentBlock = blocks[currentIdx];
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
					int current = board[row + up][j]->GetOwner();
					if (current != -1) {
						blocks[current]->RemoveCell(board[row + up][j].get());
						if (blocks[current]->GetCellsCount() == 0) {
							score += (blocks[current]->GetLevel() + 1) * (blocks[current]->GetLevel() + 1);
							blocks[current] = nullptr;
						}
					}
					board[row + up][j]->SetType('.');
					
				}
				for (int j = row + 1 + up; j < rows; j++) {
					for (int k = 0; k < cols; k++) {
						int current = board[j][k]->GetOwner();
						if (current != -1) {
							blocks[current]->RemoveCell(board[j][k].get());
							blocks[current]->AddCell(board[j - 1][k].get(), current);
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

char Board::GetHold() const {
	return hold;
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
	std::cout << "Level: " << b.currentLevel << std::endl;
	std::cout << "Score: " << b.score << std::endl;
	std::cout << "-----------" << std::endl;
	for (int i = b.rows + b.extra - 1; i >= 0; i--) {
		for (int j = 0; j < b.cols; j++) {
			if (b.blind && i >= 2 && i <= 8 && j >= 2 && j <= 11) {
				std::cout << '?';
			} else {
				std::cout << b.GetCellType(i, j);
			}
		}
		std:: cout << std::endl;
	}
    std::cout << "-----------" << std::endl;
	std::cout << "Next:" << std::endl;
	return out;
}

