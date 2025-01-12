#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board {
public:
    Board();
    void initialize();

    void initializeRow(int row, const std::string &piece);

    void initializePiece(int row, int col, const std::string &piece);

    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getColumns() const;
    [[nodiscard]] std::string getPieceAt(int row, int col) const;
    void setPieceAt(int row, int col, std::string piece);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    bool movePawn(int startRow, int startCol, int endRow, int endCol, const std::string &piece);
    bool moveRook(int startRow, int startCol, int endRow, int endCol, const std::string &piece);
    bool moveBishop(int startRow, int startCol, int endRow, int endCol, const std::string &piece);

    bool moveKnight(int startRow, int startCol, int endRow, int endCol, const std::string &piece);

    [[nodiscard]] bool isRookMoveValid(int startRow, int startCol, int endRow, int endCol) const;
    [[nodiscard]] bool isBishopMoveValid(int startRow, int startCol, int endRow, int endCol) const;

    static bool isKnightMoveValid(int startRow, int startCol, int endRow, int endCol);

private:
    std::vector<std::vector<std::string>> grid;
};

#endif
