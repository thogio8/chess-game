#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board {
public:
    Board();
    void initialize();
    int getRows() const;
    int getColumns() const;
    std::string getPieceAt(int row, int col) const;
    void setPieceAt(int row, int col, std::string piece);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    bool isRookMoveValid(int startRow, int startCol, int endRow, int endCol) const;
    bool isBishopMoveValid(int startRow, int startCol, int endRow, int endCol) const;

private:
    std::vector<std::vector<std::string>> grid;
};

#endif
