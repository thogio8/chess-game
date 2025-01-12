#include <gtest/gtest.h>
#include "include/Board.h"

TEST(BoardTest, CanCreateBoard) {
    Board board;
    EXPECT_EQ(board.getRows(), 8);
    EXPECT_EQ(board.getColumns(), 8);
}

TEST(BoardTest, InitializesPiecesCorrectly) {
    Board board;
    board.initialize();

    // Test pawns
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(board.getPieceAt(1, i), "white_pawn");
        EXPECT_EQ(board.getPieceAt(6, i), "black_pawn");
    }

    // Test rooks
    EXPECT_EQ(board.getPieceAt(0, 0), "white_rook");
    EXPECT_EQ(board.getPieceAt(0, 7), "white_rook");
    EXPECT_EQ(board.getPieceAt(7, 0), "black_rook");
    EXPECT_EQ(board.getPieceAt(7, 7), "black_rook");

    // Test knights
    EXPECT_EQ(board.getPieceAt(0, 1), "white_knight");
    EXPECT_EQ(board.getPieceAt(0, 6), "white_knight");
    EXPECT_EQ(board.getPieceAt(7, 1), "black_knight");
    EXPECT_EQ(board.getPieceAt(7, 6), "black_knight");

    // Test bishops
    EXPECT_EQ(board.getPieceAt(0, 2), "white_bishop");
    EXPECT_EQ(board.getPieceAt(0, 5), "white_bishop");
    EXPECT_EQ(board.getPieceAt(7, 2), "black_bishop");
    EXPECT_EQ(board.getPieceAt(7, 5), "black_bishop");

    // Test queens
    EXPECT_EQ(board.getPieceAt(0, 3), "white_queen");
    EXPECT_EQ(board.getPieceAt(7, 3), "black_queen");

    // Test kings
    EXPECT_EQ(board.getPieceAt(0, 4), "white_king");
    EXPECT_EQ(board.getPieceAt(7, 4), "black_king");

    // Test empty spaces
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(board.getPieceAt(i, j), "");
        }
    }
}

TEST(BoardTest, WhitePawnStandardMove) {
    Board board;
    board.initialize();

    // Valid move: White pawn moves one square forward
    EXPECT_TRUE(board.movePiece(1, 0, 2, 0));
    EXPECT_EQ(board.getPieceAt(2, 0), "white_pawn");
    EXPECT_EQ(board.getPieceAt(1, 0), "");

    // Invalid move: White pawn moves sideways
    EXPECT_FALSE(board.movePiece(2, 0, 2, 1));
}

TEST(BoardTest, BlackPawnStandardMove) {
    Board board;
    board.initialize();

    // Valid move: Black pawn moves one square forward (downward)
    EXPECT_TRUE(board.movePiece(6, 0, 5, 0));
    EXPECT_EQ(board.getPieceAt(5, 0), "black_pawn");
    EXPECT_EQ(board.getPieceAt(6, 0), "");

    // Invalid move: Black pawn moves sideways
    EXPECT_FALSE(board.movePiece(5, 0, 5, 1));
}

TEST(BoardTest, WhitePawnInitialDoubleMove) {
    Board board;
    board.initialize();

    // Valid double move: White pawn moves two squares forward from starting position
    EXPECT_TRUE(board.movePiece(1, 0, 3, 0));
    EXPECT_EQ(board.getPieceAt(3, 0), "white_pawn");
    EXPECT_EQ(board.getPieceAt(1, 0), "");
}

TEST(BoardTest, BlackPawnInitialDoubleMove) {
    Board board;
    board.initialize();

    // Valid double move: Black pawn moves two squares forward from starting position
    EXPECT_TRUE(board.movePiece(6, 0, 4, 0));
    EXPECT_EQ(board.getPieceAt(4, 0), "black_pawn");
    EXPECT_EQ(board.getPieceAt(6, 0), "");
}

TEST(BoardTest, WhitePawnCapture) {
    Board board;
    board.initialize();

    // Set up an opponent's piece for capturing
    board.setPieceAt(2, 1, "black_pawn");

    // Valid capture: White pawn captures black pawn diagonally
    EXPECT_TRUE(board.movePiece(1, 0, 2, 1));
    EXPECT_EQ(board.getPieceAt(2, 1), "white_pawn");
    EXPECT_EQ(board.getPieceAt(1, 0), "");
}

TEST(BoardTest, BlackPawnCapture) {
    Board board;
    board.initialize();

    // Set up an opponent's piece for capturing
    board.setPieceAt(5, 1, "white_pawn");

    // Valid capture: Black pawn captures white pawn diagonally
    EXPECT_TRUE(board.movePiece(6, 0, 5, 1));
    EXPECT_EQ(board.getPieceAt(5, 1), "black_pawn");
    EXPECT_EQ(board.getPieceAt(6, 0), "");
}

TEST(BoardTest, WhitePawnInvalidMoves) {
    Board board;
    board.initialize();

    // Invalid move: White pawn moves backward
    EXPECT_FALSE(board.movePiece(1, 0, 0, 0));

    // Invalid move: White pawn moves more than two squares forward
    EXPECT_FALSE(board.movePiece(1, 0, 4, 0));
}

TEST(BoardTest, BlackPawnInvalidMoves) {
    Board board;
    board.initialize();

    // Invalid move: Black pawn moves backward
    EXPECT_FALSE(board.movePiece(6, 0, 7, 0));

    // Invalid move: Black pawn moves more than two squares forward
    EXPECT_FALSE(board.movePiece(6, 0, 3, 0));
}

TEST(BoardTest, WhitePawnEnPassantCaptureSideOne) {
    Board board;
    board.initialize();

    // Set up black pawn for en passant capture
    board.setPieceAt(6, 2, "black_pawn");

    //Set up white pawn for en passant capture
    board.setPieceAt(4,1, "white_pawn");

    //Valid move the opponent's pawn two squares forward
    EXPECT_TRUE(board.movePiece(6, 2, 4, 2));
    EXPECT_EQ(board.getPieceAt(4,2), "black_pawn");
    EXPECT_EQ(board.getPieceAt(5,2), "");
    EXPECT_EQ(board.getPieceAt(6,2), "");

    // Valid en passant capture: White pawn captures black pawn en passant
    EXPECT_TRUE(board.movePiece(4, 1, 5, 2));
    EXPECT_EQ(board.getPieceAt(5, 2), "white_pawn");
    EXPECT_EQ(board.getPieceAt(4, 1), "");
    EXPECT_EQ(board.getPieceAt(4, 2), "");
}

TEST(BoardTest, WhitePawnEnPassantCaptureSideTwo) {
    Board board;
    board.initialize();

    // Set up black pawn for en passant capture
    board.setPieceAt(6, 2, "black_pawn");

    //Set up white pawn for en passant capture
    board.setPieceAt(4,3, "white_pawn");

    //Valid move the opponent's pawn two squares forward
    EXPECT_TRUE(board.movePiece(6, 2, 4, 2));
    EXPECT_EQ(board.getPieceAt(4,2), "black_pawn");
    EXPECT_EQ(board.getPieceAt(5,2), "");
    EXPECT_EQ(board.getPieceAt(6,2), "");

    // Valid en passant capture: White pawn captures black pawn en passant
    EXPECT_TRUE(board.movePiece(4, 3, 5, 2));
    EXPECT_EQ(board.getPieceAt(5, 2), "white_pawn");
    EXPECT_EQ(board.getPieceAt(4, 3), "");
    EXPECT_EQ(board.getPieceAt(4, 2), "");
}

TEST(BoardTest, BlackPawnEnPassantCaptureSideOne) {
    Board board;
    board.initialize();

    // Set up black pawn for en passant capture
    board.setPieceAt(6, 2, "black_pawn");

    //Set up white pawn for en passant capture
    board.setPieceAt(4,1, "white_pawn");

    //Valid move the opponent's pawn two squares forward
    EXPECT_TRUE(board.movePiece(6, 2, 4, 2));
    EXPECT_EQ(board.getPieceAt(4,2), "black_pawn");
    EXPECT_EQ(board.getPieceAt(5,2), "");
    EXPECT_EQ(board.getPieceAt(6,2), "");

    // Valid en passant capture: White pawn captures black pawn en passant
    EXPECT_TRUE(board.movePiece(4, 1, 5, 2));
    EXPECT_EQ(board.getPieceAt(5, 2), "white_pawn");
    EXPECT_EQ(board.getPieceAt(4, 1), "");
    EXPECT_EQ(board.getPieceAt(4, 2), "");
}

TEST(BoardTest, BlackPawnEnPassantCaptureSideTwo) {
    Board board;
    board.initialize();

    // Set up black pawn for en passant capture
    board.setPieceAt(6, 2, "black_pawn");

    //Set up white pawn for en passant capture
    board.setPieceAt(4,3, "white_pawn");

    //Valid move the opponent's pawn two squares forward
    EXPECT_TRUE(board.movePiece(6, 2, 4, 2));
    EXPECT_EQ(board.getPieceAt(4,2), "black_pawn");
    EXPECT_EQ(board.getPieceAt(5,2), "");
    EXPECT_EQ(board.getPieceAt(6,2), "");

    // Valid en passant capture: White pawn captures black pawn en passant
    EXPECT_TRUE(board.movePiece(4, 3, 5, 2));
    EXPECT_EQ(board.getPieceAt(5, 2), "white_pawn");
    EXPECT_EQ(board.getPieceAt(4, 3), "");
    EXPECT_EQ(board.getPieceAt(4, 2), "");
}

TEST(BoardTest, WhitePawnPromotion) {
    Board board;
    board.initialize();

    // Set up white pawn for promotion
    board.setPieceAt(6, 0, "white_pawn");

    // Valid promotion: White pawn promotes to either queen, rook, bishop, or knight
    EXPECT_TRUE(board.movePiece(6, 0, 7, 0));
    EXPECT_TRUE(board.getPieceAt(7, 0) == "white_queen" || board.getPieceAt(7, 0) == "white_rook" ||
                board.getPieceAt(7, 0) == "white_bishop" || board.getPieceAt(7, 0) == "white_knight");
    EXPECT_EQ(board.getPieceAt(6, 0), "");
}

TEST(BoardTest, BlackPawnPromotion) {
    Board board;
    board.initialize();

    // Set up black pawn for promotion
    board.setPieceAt(1, 0, "black_pawn");

    // Valid promotion: Black pawn promotes to either queen, rook, bishop, or knight
    EXPECT_TRUE(board.movePiece(1, 0, 0, 0));
    EXPECT_TRUE(board.getPieceAt(0, 0) == "black_queen" || board.getPieceAt(0, 0) == "black_rook" ||
                board.getPieceAt(0, 0) == "black_bishop" || board.getPieceAt(0, 0) == "black_knight");
    EXPECT_EQ(board.getPieceAt(1, 0), "");
}

// Test white rook movement
TEST(BoardTest, WhiteRookValidMoves) {
    Board board;
    board.initialize();

    board.setPieceAt(2,2,"white_rook");

    // Valid move: White rook moves vertically
    EXPECT_TRUE(board.movePiece(2, 2, 4, 2));
    EXPECT_EQ(board.getPieceAt(4, 2), "white_rook");
    EXPECT_EQ(board.getPieceAt(2, 2), "");

    board.setPieceAt(2,2,"white_rook");

    // Valid move: White rook moves horizontally
    EXPECT_TRUE(board.movePiece(2, 2, 2, 4));
    EXPECT_EQ(board.getPieceAt(2, 4), "white_rook");
    EXPECT_EQ(board.getPieceAt(2, 2), "");
}

// Test white rook invalid moves
TEST(BoardTest, WhiteRookInvalidMoves) {
    Board board;
    board.initialize();

    // Invalid move: White rook moves diagonally
    EXPECT_FALSE(board.movePiece(0, 0, 1, 1));

    // Invalid move: White rook moves like a knight
    EXPECT_FALSE(board.movePiece(0, 0, 2, 1));

    // Invalid move: White rook jumps over a piece
    board.setPieceAt(2, 0, "black_pawn");
    EXPECT_FALSE(board.movePiece(0, 0, 4, 0));
    EXPECT_EQ(board.getPieceAt(2, 0), "black_pawn");
    EXPECT_EQ(board.getPieceAt(0, 0), "white_rook");
}

// Test black rook movement
TEST(BoardTest, BlackRookValidMoves) {
    Board board;
    board.initialize();

    board.setPieceAt(5,0,"black_rook");

    // Valid move: Black rook moves vertically
    EXPECT_TRUE(board.movePiece(5, 0, 3, 0));
    EXPECT_EQ(board.getPieceAt(3, 0), "black_rook");
    EXPECT_EQ(board.getPieceAt(5, 0), "");

    board.setPieceAt(5,0,"black_rook");

    // Valid move: Black rook moves horizontally
    EXPECT_TRUE(board.movePiece(5, 0, 5, 4));
    EXPECT_EQ(board.getPieceAt(5, 4), "black_rook");
    EXPECT_EQ(board.getPieceAt(5, 0), "");
}

// Test black rook invalid moves
TEST(BoardTest, BlackRookInvalidMoves) {
    Board board;
    board.initialize();

    // Invalid move: Black rook moves diagonally
    EXPECT_FALSE(board.movePiece(7, 0, 6, 1));

    // Invalid move: Black rook moves like a knight
    EXPECT_FALSE(board.movePiece(7, 0, 5, 1));

    // Invalid move: Black rook jumps over a piece
    board.setPieceAt(5, 0, "white_pawn");
    EXPECT_FALSE(board.movePiece(7, 0, 3, 0));
    EXPECT_EQ(board.getPieceAt(5, 0), "white_pawn");
    EXPECT_EQ(board.getPieceAt(7, 0), "black_rook");
}

// Test white rook capture
TEST(BoardTest, WhiteRookCapture) {
    Board board;
    board.initialize();

    // Set up a white rook for capturing
    board.setPieceAt(2, 0, "white_rook");

    // Set up an opponent's piece for capturing
    board.setPieceAt(4, 0, "black_pawn");

    // Valid capture: White rook captures black pawn
    EXPECT_TRUE(board.movePiece(2, 0, 4, 0));
    EXPECT_EQ(board.getPieceAt(4, 0), "white_rook");
    EXPECT_EQ(board.getPieceAt(2, 0), "");
}

// Test black rook capture
TEST(BoardTest, BlackRookCapture) {
    Board board;
    board.initialize();

    // Set up a black rook for capturing
    board.setPieceAt(5, 0, "black_rook");

    // Set up an opponent's piece for capturing
    board.setPieceAt(3, 0, "white_pawn");

    // Valid capture: Black rook captures white pawn
    EXPECT_TRUE(board.movePiece(5, 0, 3, 0));
    EXPECT_EQ(board.getPieceAt(3, 0), "black_rook");
    EXPECT_EQ(board.getPieceAt(5, 0), "");
}

// Test white rook capturing own piece
TEST(BoardTest, WhiteRookCaptureOwnPiece) {
    Board board;
    board.initialize();

    // Set up a white rook for capturing
    board.setPieceAt(2, 0, "white_rook");

    // Set up a white piece for capturing
    board.setPieceAt(4, 0, "white_pawn");

    // Invalid capture: White rook captures white pawn
    EXPECT_FALSE(board.movePiece(2, 0, 4, 0));
    EXPECT_EQ(board.getPieceAt(2, 0), "white_rook");
    EXPECT_EQ(board.getPieceAt(4, 0), "white_pawn");
}

// Test black rook capturing own piece
TEST(BoardTest, BlackRookCaptureOwnPiece) {
    Board board;
    board.initialize();

    // Set up a black rook for capturing
    board.setPieceAt(5, 0, "black_rook");

    // Set up a black piece for capturing
    board.setPieceAt(3, 0, "black_pawn");

    // Invalid capture: Black rook captures black pawn
    EXPECT_FALSE(board.movePiece(5, 0, 3, 0));
    EXPECT_EQ(board.getPieceAt(5, 0), "black_rook");
    EXPECT_EQ(board.getPieceAt(3, 0), "black_pawn");
}

// Test white bishop valid moves
TEST(BoardTest, WhiteBishopValidMoves) {
    Board board;
    board.initialize();

    board.setPieceAt(2,2,"white_bishop");

    // Valid move: Bishop moves diagonally
    EXPECT_TRUE(board.movePiece(2, 2, 4, 4));
    EXPECT_EQ(board.getPieceAt(4, 4), "white_bishop");
    EXPECT_EQ(board.getPieceAt(2, 2), "");

    board.setPieceAt(4,4,"white_bishop");

    // Valid move: Bishop moves diagonally
    EXPECT_TRUE(board.movePiece(4,4,2,2));
    EXPECT_EQ(board.getPieceAt(2, 2), "white_bishop");
    EXPECT_EQ(board.getPieceAt(4, 4), "");
}

// Test white bishop invalid moves
TEST(BoardTest, WhiteBishopInvalidMoves) {
    Board board;
    board.initialize();

    board.setPieceAt(2,2,"white_bishop");

    // Invalid move: Bishop moves vertically
    EXPECT_FALSE(board.movePiece(2, 2, 4, 2));

    // Invalid move: Bishop moves horizontally
    EXPECT_FALSE(board.movePiece(2, 2, 2, 4));

    // Invalid move: Bishop jumps over a piece
    board.setPieceAt(3, 3, "black_pawn");
    EXPECT_FALSE(board.movePiece(2, 2, 4, 4));
    EXPECT_EQ(board.getPieceAt(3, 3), "black_pawn");
    EXPECT_EQ(board.getPieceAt(2, 2), "white_bishop");
    EXPECT_EQ(board.getPieceAt(4,4), "");
}

// Test black bishop valid moves
TEST(BoardTest, BlackBishopValidMoves) {
    Board board;
    board.initialize();

    board.setPieceAt(5,0,"black_bishop");

    // Valid move: Bishop moves diagonally
    EXPECT_TRUE(board.movePiece(5, 0, 3, 2));
    EXPECT_EQ(board.getPieceAt(3, 2), "black_bishop");
    EXPECT_EQ(board.getPieceAt(5, 0), "");

    board.setPieceAt(3,2,"black_bishop");

    // Valid move: Bishop moves diagonally
    EXPECT_TRUE(board.movePiece(3,2,5,0));
    EXPECT_EQ(board.getPieceAt(5, 0), "black_bishop");
    EXPECT_EQ(board.getPieceAt(3, 2), "");
}

// Test black bishop invalid moves
TEST(BoardTest, BlackBishopInvalidMoves) {
    Board board;
    board.initialize();

    board.setPieceAt(5,0,"black_bishop");

    // Invalid move: Bishop moves vertically
    EXPECT_FALSE(board.movePiece(5, 0, 3, 0));

    // Invalid move: Bishop moves horizontally
    EXPECT_FALSE(board.movePiece(5, 0, 5, 4));

    // Invalid move: Bishop jumps over a piece
    board.setPieceAt(4, 1, "white_pawn");
    EXPECT_FALSE(board.movePiece(5, 0, 3, 2));
    EXPECT_EQ(board.getPieceAt(4, 1), "white_pawn");
    EXPECT_EQ(board.getPieceAt(5, 0), "black_bishop");
    EXPECT_EQ(board.getPieceAt(3,2), "");
}

// Test white bishop capture
TEST(BoardTest, WhiteBishopCapture) {
    Board board;
    board.initialize();

    // Set up a white bishop for capturing
    board.setPieceAt(2, 2, "white_bishop");

    // Set up an opponent's piece for capturing
    board.setPieceAt(4, 4, "black_pawn");

    // Valid capture: White bishop captures black pawn
    EXPECT_TRUE(board.movePiece(2, 2, 4, 4));
    EXPECT_EQ(board.getPieceAt(4, 4), "white_bishop");
    EXPECT_EQ(board.getPieceAt(2, 2), "");
}

// Test black bishop capture
TEST(BoardTest, BlackBishopCapture) {
    Board board;
    board.initialize();

    // Set up a black bishop for capturing
    board.setPieceAt(5, 0, "black_bishop");

    // Set up an opponent's piece for capturing
    board.setPieceAt(3, 2, "white_pawn");

    // Valid capture: Black bishop captures white pawn
    EXPECT_TRUE(board.movePiece(5, 0, 3, 2));
    EXPECT_EQ(board.getPieceAt(3, 2), "black_bishop");
    EXPECT_EQ(board.getPieceAt(5, 0), "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
