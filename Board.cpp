#include <utility>
#include "include/Board.h"

Board::Board() : grid(8, std::vector<std::string>(8, "")) {}

void Board::initialize() {
    initializeRow(1, "white_pawn");
    initializeRow(6, "black_pawn");

    initializePiece(0, 0, "white_rook");
    initializePiece(0, 7, "white_rook");
    initializePiece(7, 0, "black_rook");
    initializePiece(7, 7, "black_rook");

    initializePiece(0, 1, "white_knight");
    initializePiece(0, 6, "white_knight");
    initializePiece(7, 1, "black_knight");
    initializePiece(7, 6, "black_knight");

    initializePiece(0, 2, "white_bishop");
    initializePiece(0, 5, "white_bishop");
    initializePiece(7, 2, "black_bishop");
    initializePiece(7, 5, "black_bishop");

    initializePiece(0, 3, "white_queen");
    initializePiece(7, 3, "black_queen");

    initializePiece(0, 4, "white_king");
    initializePiece(7, 4, "black_king");
}

void Board::initializeRow(int row, const std::string& piece) {
    for (int i = 0; i < 8; i++) {
        grid[row][i] = piece;
    }
}

void Board::initializePiece(int row, int col, const std::string& piece) {
    grid[row][col] = piece;
}

int Board::getRows() const {
    return grid.size();
}

int Board::getColumns() const {
    return grid[0].size();
}

std::string Board::getPieceAt(int row, int col) const {
    return grid[row][col];
}

void Board::setPieceAt(int row, int col, std::string piece) {
    grid[row][col] = std::move(piece);
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    std::string piece = getPieceAt(startRow, startCol);

    if (piece == "white_pawn" || piece == "black_pawn") {
        return movePawn(startRow, startCol, endRow, endCol, piece);
    } else if (piece == "white_rook" || piece == "black_rook") {
        return moveRook(startRow, startCol, endRow, endCol, piece);
    } else if (piece == "white_bishop" || piece == "black_bishop") {
        return moveBishop(startRow, startCol, endRow, endCol, piece);
    }

    return false;
}

bool Board::movePawn(int startRow, int startCol, int endRow, int endCol, const std::string& piece) {
    int direction = (piece == "white_pawn") ? 1 : -1;
    std::string opponent = (piece == "white_pawn") ? "black" : "white";

    if (startRow + direction == endRow && startCol == endCol && grid[endRow][endCol].empty()) {
        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = "";
        return true;
    }
    if (startRow + 2 * direction == endRow && startCol == endCol && grid[startRow + direction][endCol].empty() && grid[endRow][endCol].empty()) {
        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = "";
        return true;
    }
    if (startRow + direction == endRow && (endCol == startCol + 1 || endCol == startCol - 1) && grid[endRow][endCol].find(opponent) != std::string::npos) {
        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = "";
        return true;
    }
    if (startRow + direction == endRow && (endCol == startCol + 1 || endCol == startCol - 1) && grid[startRow][endCol] == opponent + "_pawn" && grid[endRow][endCol].empty()) {
        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = "";
        grid[startRow][endCol] = "";
        return true;
    }
    if (startRow == (piece == "white_pawn" ? 6 : 1) && endRow == (piece == "white_pawn" ? 7 : 0) && startCol == endCol) {
        grid[endRow][endCol] = (piece == "white_pawn") ? "white_queen" : "black_queen";
        grid[startRow][startCol] = "";
        return true;
    }

    return false;
}

bool Board::moveRook(int startRow, int startCol, int endRow, int endCol, const std::string& piece) {
    if (!isRookMoveValid(startRow, startCol, endRow, endCol)) return false;
    std::string targetPiece = getPieceAt(endRow, endCol);
    if (!targetPiece.empty() && targetPiece.substr(0, 5) == piece.substr(0, 5)) return false; // Prevent capturing own piece

    grid[endRow][endCol] = piece;
    grid[startRow][startCol] = "";
    return true;
}

bool Board::moveBishop(int startRow, int startCol, int endRow, int endCol, const std::string& piece) {
    if (!isBishopMoveValid(startRow, startCol, endRow, endCol)) return false;
    std::string targetPiece = getPieceAt(endRow, endCol);
    if (!targetPiece.empty() && targetPiece.substr(0, 5) == piece.substr(0, 5)) return false; // Prevent capturing own piece

    grid[endRow][endCol] = piece;
    grid[startRow][startCol] = "";
    return true;
}

bool Board::isRookMoveValid(int startRow, int startCol, int endRow, int endCol) const {
    if (startRow == endRow) {
        int minCol = std::min(startCol, endCol);
        int maxCol = std::max(startCol, endCol);
        for (int col = minCol + 1; col < maxCol; ++col) {
            if (!grid[startRow][col].empty()) return false;
        }
        return true;
    }
    if (startCol == endCol) {
        int minRow = std::min(startRow, endRow);
        int maxRow = std::max(startRow, endRow);
        for (int row = minRow + 1; row < maxRow; ++row) {
            if (!grid[row][startCol].empty()) return false;
        }
        return true;
    }
    return false;
}

bool Board::isBishopMoveValid(int startRow, int startCol, int endRow, int endCol) const {
    if (abs(startRow - endRow) != abs(startCol - endCol)) return false;
    int rowDir = (endRow - startRow) / abs(endRow - startRow);
    int colDir = (endCol - startCol) / abs(endCol - startCol);
    for (int i = 1; i < abs(startRow - endRow); ++i) {
        if (!grid[startRow + i * rowDir][startCol + i * colDir].empty()) return false;
    }
    return true;
}