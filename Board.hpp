#pragma once

#include <SFML/System/Vector2.hpp>
#include "Utilities.hpp"
#include <bitset>
#include <vector>

using namespace std;

class Board {
    public:
        uint64_t occupiedSquares = 0;
        uint64_t whitePawns = 0;
        uint64_t whiteKnights = 0;
        uint64_t whiteBishops = 0;
        uint64_t whiteRooks = 0;
        uint64_t whiteQueens = 0;
        uint64_t whiteKing = 0;
        uint64_t blackPawns = 0;
        uint64_t blackKnights = 0;
        uint64_t blackBishops = 0;
        uint64_t blackRooks = 0;
        uint64_t blackQueens = 0;
        uint64_t blackKing = 0;
        uint64_t whitePieces = 0;
        uint64_t blackPieces = 0;
        uint64_t noMoves = 0;
        uint64_t canEnPassant = 0;
        uint64_t passant = 0;

        uint64_t* boardFlags[18] = {&occupiedSquares,
        &whitePawns, &whiteKnights, &whiteBishops, &whiteRooks, &whiteQueens, &whiteKing,
        &blackPawns, &blackKnights, &blackBishops, &blackRooks, &blackQueens, &blackKing,
        &whitePieces, &blackPieces, &noMoves, &canEnPassant, &passant};

        void setBoard(int layout[][8]);

        void setBit(uint64_t* flag, int index);

        void clearBit(uint64_t* flag, int index);

        bool hasBit(uint64_t* flag, int index);

        bool isOccupied(int index);

        bool isWhite(int index);

        bool isBlack(int index);

        int getTeam(int index);

        int getX(int index);
        
        int getY(int index);

        bool isInCheck(int king);

        bool isCheckMate(int king);

    public:
        Board(int layout[][8]);

        Board(Board& other);

        int getIndex(int x, int y);

        vector<Move> getPossMoves(int pieceIndex, int searchType);

        void movePiece(Move move);

        //void movePiece(int startIndex, Vector2i);

        bool isAttacked(int index, int team);
};