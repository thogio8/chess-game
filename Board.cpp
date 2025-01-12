#include <utility>

#include "include/Board.h"

Board::Board() : grid(8, std::vector<std::string>(8, "")) {}

void Board::initialize() {
    // Initialize pawns
    for (int i = 0; i < 8; i++) {
        grid[1][i] = "white_pawn";  // White pawns
        grid[6][i] = "black_pawn";  // Black pawns
    }

    // Initialize rooks
    grid[0][0] = "white_rook";
    grid[0][7] = "white_rook";
    grid[7][0] = "black_rook";
    grid[7][7] = "black_rook";

    // Initialize knights
    grid[0][1] = "white_knight";
    grid[0][6] = "white_knight";
    grid[7][1] = "black_knight";
    grid[7][6] = "black_knight";

    // Initialize bishops
    grid[0][2] = "white_bishop";
    grid[0][5] = "white_bishop";
    grid[7][2] = "black_bishop";
    grid[7][5] = "black_bishop";

    // Initialize queens
    grid[0][3] = "white_queen";
    grid[7][3] = "black_queen";

    // Initialize kings
    grid[0][4] = "white_king";
    grid[7][4] = "black_king";
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

    if (piece == "white_pawn") {
        if (startRow == 1 && endRow == 3 && startCol == endCol && grid[2][endCol].empty() && grid[3][endCol].empty()) {
            grid[endRow][endCol] = "white_pawn";
            grid[startRow][startCol] = "";
            return true;
        }
        if (endRow == startRow + 1 && startCol == endCol && grid[endRow][endCol].empty()) {
            grid[endRow][endCol] = "white_pawn";
            grid[startRow][startCol] = "";
            return true;
        }
        if (endRow == startRow + 1 && (endCol == startCol + 1 || endCol == startCol - 1) && grid[endRow][endCol].find("black") != std::string::npos) {
            grid[endRow][endCol] = "white_pawn";
            grid[startRow][startCol] = "";
            return true;
        }
        if (startRow == 4 && endRow == 5 && (endCol == startCol + 1 || endCol == startCol - 1) && grid[4][endCol].find("black") != std::string::npos) {
            grid[endRow][endCol] = "white_pawn";
            grid[startRow][endCol] = "";
            grid[startRow][startCol] = "";
            return true;
        }
        if (startRow == 6 && endRow == 7 && startCol == endCol) {
            grid[endRow][endCol] = "white_queen";
            grid[startRow][startCol] = "";
            return true;
        }
    }else if (piece == "black_pawn") {
        if (startRow == 6 && endRow == 4 && startCol == endCol && grid[5][endCol].empty() && grid[4][endCol].empty()) {
            grid[endRow][endCol] = "black_pawn";
            grid[startRow][startCol] = "";
            return true;
        }
        if (endRow == startRow - 1 && startCol == endCol && grid[endRow][endCol].empty()) {
            grid[endRow][endCol] = "black_pawn";
            grid[startRow][startCol] = "";
            return true;
        }
        if (endRow == startRow - 1 && (endCol == startCol + 1 || endCol == startCol - 1) && grid[endRow][endCol].find("white") != std::string::npos) {
            grid[endRow][endCol] = "black_pawn";
            grid[startRow][startCol] = "";
            return true;
        }
        if (startRow == 3 && endRow == 2 && (endCol == startCol + 1 || endCol == startCol - 1) && grid[3][endCol].find("white") != std::string::npos) {
            grid[endRow][endCol] = "black_pawn";
            grid[startRow][endCol] = "";
            grid[startRow][startCol] = "";
            return true;
        }
        if (startRow == 1 && endRow == 0 && startCol == endCol) {
            grid[endRow][endCol] = "black_queen";
            grid[startRow][startCol] = "";
            return true;
        }
    }else if (piece == "white_rook" || piece == "black_rook") {
        if (!isRookMoveValid(startRow, startCol, endRow, endCol)) return false;
        std::string targetPiece = getPieceAt(endRow, endCol);
        if (!targetPiece.empty() && targetPiece.substr(0, 5) == piece.substr(0, 5)) return false; // Prevent capturing own piece

        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = "";
        return true;
    }else if (piece == "white_bishop" || piece == "black_bishop") {
        if (!isBishopMoveValid(startRow, startCol, endRow, endCol)) return false;
        std::string targetPiece = getPieceAt(endRow, endCol);
        if (!targetPiece.empty() && targetPiece.substr(0, 5) == piece.substr(0, 5)) return false; // Prevent capturing own piece

        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = "";
        return true;
    }

    return false;
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
