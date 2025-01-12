#include <gtest/gtest.h>
#include "include/Board.h"

class BoardTest : public ::testing::Test {
protected:
    Board board;

    void SetUp() override {
        board.initialize();
    }

    void expectPieceAt(int row, int col, const std::string& piece) const {
        EXPECT_EQ(board.getPieceAt(row, col), piece);
    }

    void expectEmptyAt(int row, int col) const {
        EXPECT_EQ(board.getPieceAt(row, col), "");
    }

    void expectMovePiece(int startRow, int startCol, int endRow, int endCol, bool expected) {
        EXPECT_EQ(board.movePiece(startRow, startCol, endRow, endCol), expected);
    }
};

TEST_F(BoardTest, CanCreateBoard) {
    EXPECT_EQ(board.getRows(), 8);
    EXPECT_EQ(board.getColumns(), 8);
}

TEST_F(BoardTest, InitializesPiecesCorrectly) {
    for (int i = 0; i < 8; i++) {
        expectPieceAt(1, i, "white_pawn");
        expectPieceAt(6, i, "black_pawn");
    }

    expectPieceAt(0, 0, "white_rook");
    expectPieceAt(0, 7, "white_rook");
    expectPieceAt(7, 0, "black_rook");
    expectPieceAt(7, 7, "black_rook");

    expectPieceAt(0, 1, "white_knight");
    expectPieceAt(0, 6, "white_knight");
    expectPieceAt(7, 1, "black_knight");
    expectPieceAt(7, 6, "black_knight");

    expectPieceAt(0, 2, "white_bishop");
    expectPieceAt(0, 5, "white_bishop");
    expectPieceAt(7, 2, "black_bishop");
    expectPieceAt(7, 5, "black_bishop");

    expectPieceAt(0, 3, "white_queen");
    expectPieceAt(7, 3, "black_queen");

    expectPieceAt(0, 4, "white_king");
    expectPieceAt(7, 4, "black_king");

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            expectEmptyAt(i, j);
        }
    }
}

TEST_F(BoardTest, WhitePawnStandardMove) {
    expectMovePiece(1, 0, 2, 0, true);
    expectPieceAt(2, 0, "white_pawn");
    expectEmptyAt(1, 0);

    expectMovePiece(2, 0, 2, 1, false);
}

TEST_F(BoardTest, BlackPawnStandardMove) {
    expectMovePiece(6, 0, 5, 0, true);
    expectPieceAt(5, 0, "black_pawn");
    expectEmptyAt(6, 0);

    expectMovePiece(5, 0, 5, 1, false);
}

TEST_F(BoardTest, WhitePawnInitialDoubleMove) {
    expectMovePiece(1, 0, 3, 0, true);
    expectPieceAt(3, 0, "white_pawn");
    expectEmptyAt(1, 0);
}

TEST_F(BoardTest, BlackPawnInitialDoubleMove) {
    expectMovePiece(6, 0, 4, 0, true);
    expectPieceAt(4, 0, "black_pawn");
    expectEmptyAt(6, 0);
}

TEST_F(BoardTest, WhitePawnCapture) {
    board.setPieceAt(2, 1, "black_pawn");
    expectMovePiece(1, 0, 2, 1, true);
    expectPieceAt(2, 1, "white_pawn");
    expectEmptyAt(1, 0);
}

TEST_F(BoardTest, BlackPawnCapture) {
    board.setPieceAt(5, 1, "white_pawn");
    expectMovePiece(6, 0, 5, 1, true);
    expectPieceAt(5, 1, "black_pawn");
    expectEmptyAt(6, 0);
}

TEST_F(BoardTest, WhitePawnInvalidMoves) {
    expectMovePiece(1, 0, 0, 0, false);
    expectMovePiece(1, 0, 4, 0, false);
}

TEST_F(BoardTest, BlackPawnInvalidMoves) {
    expectMovePiece(6, 0, 7, 0, false);
    expectMovePiece(6, 0, 3, 0, false);
}

TEST_F(BoardTest, WhitePawnEnPassantCaptureSideOne) {
    board.setPieceAt(6, 2, "black_pawn");
    board.setPieceAt(4, 1, "white_pawn");
    expectMovePiece(6, 2, 4, 2, true);
    expectPieceAt(4, 2, "black_pawn");
    expectEmptyAt(5, 2);
    expectEmptyAt(6, 2);
    expectMovePiece(4, 1, 5, 2, true);
    expectPieceAt(5, 2, "white_pawn");
    expectEmptyAt(4, 1);
    expectEmptyAt(4, 2);
}

TEST_F(BoardTest, WhitePawnEnPassantCaptureSideTwo) {
    board.setPieceAt(6, 2, "black_pawn");
    board.setPieceAt(4, 3, "white_pawn");
    expectMovePiece(6, 2, 4, 2, true);
    expectPieceAt(4, 2, "black_pawn");
    expectEmptyAt(5, 2);
    expectEmptyAt(6, 2);
    expectMovePiece(4, 3, 5, 2, true);
    expectPieceAt(5, 2, "white_pawn");
    expectEmptyAt(4, 3);
    expectEmptyAt(4, 2);
}

TEST_F(BoardTest, BlackPawnEnPassantCaptureSideOne) {
    board.setPieceAt(6, 2, "black_pawn");
    board.setPieceAt(4, 1, "white_pawn");
    expectMovePiece(6, 2, 4, 2, true);
    expectPieceAt(4, 2, "black_pawn");
    expectEmptyAt(5, 2);
    expectEmptyAt(6, 2);
    expectMovePiece(4, 1, 5, 2, true);
    expectPieceAt(5, 2, "white_pawn");
    expectEmptyAt(4, 1);
    expectEmptyAt(4, 2);
}

TEST_F(BoardTest, BlackPawnEnPassantCaptureSideTwo) {
    board.setPieceAt(6, 2, "black_pawn");
    board.setPieceAt(4, 3, "white_pawn");
    expectMovePiece(6, 2, 4, 2, true);
    expectPieceAt(4, 2, "black_pawn");
    expectEmptyAt(5, 2);
    expectEmptyAt(6, 2);
    expectMovePiece(4, 3, 5, 2, true);
    expectPieceAt(5, 2, "white_pawn");
    expectEmptyAt(4, 3);
    expectEmptyAt(4, 2);
}

TEST_F(BoardTest, WhitePawnPromotion) {
    board.setPieceAt(6, 0, "white_pawn");
    expectMovePiece(6, 0, 7, 0, true);
    EXPECT_TRUE(board.getPieceAt(7, 0) == "white_queen" || board.getPieceAt(7, 0) == "white_rook" ||
                board.getPieceAt(7, 0) == "white_bishop" || board.getPieceAt(7, 0) == "white_knight");
    expectEmptyAt(6, 0);
}

TEST_F(BoardTest, BlackPawnPromotion) {
    board.setPieceAt(1, 0, "black_pawn");
    expectMovePiece(1, 0, 0, 0, true);
    EXPECT_TRUE(board.getPieceAt(0, 0) == "black_queen" || board.getPieceAt(0, 0) == "black_rook" ||
                board.getPieceAt(0, 0) == "black_bishop" || board.getPieceAt(0, 0) == "black_knight");
    expectEmptyAt(1, 0);
}

TEST_F(BoardTest, WhiteRookValidMoves) {
    board.setPieceAt(2, 2, "white_rook");
    expectMovePiece(2, 2, 4, 2, true);
    expectPieceAt(4, 2, "white_rook");
    expectEmptyAt(2, 2);

    board.setPieceAt(2, 2, "white_rook");
    expectMovePiece(2, 2, 2, 4, true);
    expectPieceAt(2, 4, "white_rook");
    expectEmptyAt(2, 2);
}

TEST_F(BoardTest, WhiteRookInvalidMoves) {
    expectMovePiece(0, 0, 1, 1, false);
    expectMovePiece(0, 0, 2, 1, false);

    board.setPieceAt(2, 0, "black_pawn");
    expectMovePiece(0, 0, 4, 0, false);
    expectPieceAt(2, 0, "black_pawn");
    expectPieceAt(0, 0, "white_rook");
}

TEST_F(BoardTest, BlackRookValidMoves) {
    board.setPieceAt(5, 0, "black_rook");
    expectMovePiece(5, 0, 3, 0, true);
    expectPieceAt(3, 0, "black_rook");
    expectEmptyAt(5, 0);

    board.setPieceAt(5, 0, "black_rook");
    expectMovePiece(5, 0, 5, 4, true);
    expectPieceAt(5, 4, "black_rook");
    expectEmptyAt(5, 0);
}

TEST_F(BoardTest, BlackRookInvalidMoves) {
    expectMovePiece(7, 0, 6, 1, false);
    expectMovePiece(7, 0, 5, 1, false);

    board.setPieceAt(5, 0, "white_pawn");
    expectMovePiece(7, 0, 3, 0, false);
    expectPieceAt(5, 0, "white_pawn");
    expectPieceAt(7, 0, "black_rook");
}

TEST_F(BoardTest, WhiteRookCapture) {
    board.setPieceAt(2, 0, "white_rook");
    board.setPieceAt(4, 0, "black_pawn");
    expectMovePiece(2, 0, 4, 0, true);
    expectPieceAt(4, 0, "white_rook");
    expectEmptyAt(2, 0);
}

TEST_F(BoardTest, BlackRookCapture) {
    board.setPieceAt(5, 0, "black_rook");
    board.setPieceAt(3, 0, "white_pawn");
    expectMovePiece(5, 0, 3, 0, true);
    expectPieceAt(3, 0, "black_rook");
    expectEmptyAt(5, 0);
}

TEST_F(BoardTest, WhiteRookCaptureOwnPiece) {
    board.setPieceAt(2, 0, "white_rook");
    board.setPieceAt(4, 0, "white_pawn");
    expectMovePiece(2, 0, 4, 0, false);
    expectPieceAt(2, 0, "white_rook");
    expectPieceAt(4, 0, "white_pawn");
}

TEST_F(BoardTest, BlackRookCaptureOwnPiece) {
    board.setPieceAt(5, 0, "black_rook");
    board.setPieceAt(3, 0, "black_pawn");
    expectMovePiece(5, 0, 3, 0, false);
    expectPieceAt(5, 0, "black_rook");
    expectPieceAt(3, 0, "black_pawn");
}

TEST_F(BoardTest, WhiteBishopValidMoves) {
    board.setPieceAt(2, 2, "white_bishop");
    expectMovePiece(2, 2, 4, 4, true);
    expectPieceAt(4, 4, "white_bishop");
    expectEmptyAt(2, 2);

    board.setPieceAt(4, 4, "white_bishop");
    expectMovePiece(4, 4, 2, 2, true);
    expectPieceAt(2, 2, "white_bishop");
    expectEmptyAt(4, 4);
}

TEST_F(BoardTest, WhiteBishopInvalidMoves) {
    board.setPieceAt(2, 2, "white_bishop");
    expectMovePiece(2, 2, 4, 2, false);
    expectMovePiece(2, 2, 2, 4, false);

    board.setPieceAt(3, 3, "black_pawn");
    expectMovePiece(2, 2, 4, 4, false);
    expectPieceAt(3, 3, "black_pawn");
    expectPieceAt(2, 2, "white_bishop");
    expectEmptyAt(4, 4);
}

TEST_F(BoardTest, BlackBishopValidMoves) {
    board.setPieceAt(5, 0, "black_bishop");
    expectMovePiece(5, 0, 3, 2, true);
    expectPieceAt(3, 2, "black_bishop");
    expectEmptyAt(5, 0);

    board.setPieceAt(3, 2, "black_bishop");
    expectMovePiece(3, 2, 5, 0, true);
    expectPieceAt(5, 0, "black_bishop");
    expectEmptyAt(3, 2);
}

TEST_F(BoardTest, BlackBishopInvalidMoves) {
    board.setPieceAt(5, 0, "black_bishop");
    expectMovePiece(5, 0, 3, 0, false);
    expectMovePiece(5, 0, 5, 4, false);

    board.setPieceAt(4, 1, "white_pawn");
    expectMovePiece(5, 0, 3, 2, false);
    expectPieceAt(4, 1, "white_pawn");
    expectPieceAt(5, 0, "black_bishop");
    expectEmptyAt(3, 2);
}

TEST_F(BoardTest, WhiteBishopCapture) {
    board.setPieceAt(2, 2, "white_bishop");
    board.setPieceAt(4, 4, "black_pawn");
    expectMovePiece(2, 2, 4, 4, true);
    expectPieceAt(4, 4, "white_bishop");
    expectEmptyAt(2, 2);
}

TEST_F(BoardTest, BlackBishopCapture) {
    board.setPieceAt(5, 0, "black_bishop");
    board.setPieceAt(3, 2, "white_pawn");
    expectMovePiece(5, 0, 3, 2, true);
    expectPieceAt(3, 2, "black_bishop");
    expectEmptyAt(5, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}