#include "Board.hpp"

#include <bitset>
#include <vector>
#include <iostream>

using namespace std;

void Board::setBoard(int layout[][8]){

    /*for(int i = 0; i < sizeof(boardFlags); i++)
        **(boardFlags + i) = 0;/**/

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            int index = (7 - x) + ((7 - y) * 8);
            switch(layout[y][x]){
                case 1:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[1], index);
                    setBit(boardFlags[13], index);
                    break;
                case 2:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[2], index);
                    setBit(boardFlags[13], index);
                    break;
                case 3:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[3], index);
                    setBit(boardFlags[13], index);
                    break;
                case 4:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[4], index);
                    setBit(boardFlags[13], index);
                    break;
                case 5:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[5], index);
                    setBit(boardFlags[13], index);
                    break;
                case 6:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[6], index);
                    setBit(boardFlags[13], index);
                    break;

                case -1:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[7], index);
                    setBit(boardFlags[14], index);
                    break;
                case -2:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[8], index);
                    setBit(boardFlags[14], index);
                    break;
                case -3:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[9], index);
                    setBit(boardFlags[14], index);
                    break;
                case -4:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[10], index);
                    setBit(boardFlags[14], index);
                    break;
                case -5:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[11], index);
                    setBit(boardFlags[14], index);
                    break;
                case -6:
                    setBit(boardFlags[0], index);
                    setBit(boardFlags[12], index);
                    setBit(boardFlags[14], index);
                    break;
            }
        }
    }

    for(int i = 1; i <= 6; i++){
        *boardFlags[13] |= *boardFlags[i];
    }

    for(int i = 7; i <= 12; i++){
        *boardFlags[14] |= *boardFlags[i];
    }

    *boardFlags[15] = *boardFlags[0];
}

void Board::setBit(uint64_t* flag, int index){
    *flag |= 1ULL << index;
}

void Board::clearBit(uint64_t* flag, int index){
    *flag &= ~(1ULL << index);
}

bool Board::hasBit(uint64_t* flag, int index){
    return *flag & 1ULL << index;
}

bool Board::isOccupied(int index){
    return *boardFlags[0] & (1ULL << index);
}

bool Board::isWhite(int index){
    return *boardFlags[13] & (1ULL << index);
}

bool Board::isBlack(int index){
    return *boardFlags[14] & (1ULL << index);
}

int Board::getTeam(int index){
    return (isWhite(index)) ? 0 : 1;
}

int Board::getIndex(int x, int y){
    return (7 - x) + ((7 - y) * 8);
}

int Board::getX(int index){
    return 7 - (index % 8);
}

int Board::getY(int index){
    return 7 - (index / 8);
}

Board::Board(int layout[][8]){
    Board::setBoard(layout);
}

Board::Board(Board& other){
    occupiedSquares = other.occupiedSquares;
    whitePawns = other.whitePawns;
    whiteKnights = other.whiteKnights;
    whiteBishops = other.whiteBishops;
    whiteRooks = other.whiteRooks;
    whiteQueens = other.whiteQueens;
    whiteKing = other.whiteKing;
    blackPawns = other.blackPawns;
    blackKnights = other.blackKnights;
    blackBishops = other.blackBishops;
    blackRooks = other.blackRooks;
    blackQueens = other.blackQueens;
    blackKing = other.blackKing;
    whitePieces = other.whitePieces;
    blackPieces = other.blackPieces;
    noMoves = other.noMoves;
}

void Board::movePiece(Move move){
    //cout << move.startIndex << "," << move.targetIndex << "," << move.specialType << "\n";
    if(move.specialType & enPassant){
        int moveDir = (move.targetIndex - move.startIndex > 0) ? 1 : -1;
        movePiece({move.startIndex, move.targetIndex - (8 * moveDir), 0});
        movePiece({move.targetIndex - (8 * moveDir), move.targetIndex, 0});
        *boardFlags[16] = 0;
        *boardFlags[17] = 0;
        return;
    }

    if(move.specialType & doubleMove){
        int moveDir = (move.targetIndex - move.startIndex > 0) ? 1 : -1;
        setBit(boardFlags[16], move.targetIndex + 1);
        setBit(boardFlags[16], move.targetIndex - 1);
        setBit(boardFlags[17], move.targetIndex);
    } else {
        *boardFlags[16] = 0;
        *boardFlags[17] = 0;
    }

    if(move.specialType & castling){
        if(hasBit(boardFlags[0], move.targetIndex)){
            if(move.targetIndex < move.startIndex){
                movePiece({move.startIndex, move.startIndex - 2, 0});
                movePiece({move.startIndex - 3, move.startIndex - 1, 0});
            } else {
                movePiece({move.startIndex, move.startIndex + 2, 0});
                movePiece({move.startIndex + 4, move.startIndex + 1, 0});
            }
        } else {
            if(move.targetIndex < move.startIndex){
                movePiece({move.startIndex, move.startIndex - 2, 0});
                movePiece({move.startIndex - 3, move.startIndex - 1, 0});
            } else {
                movePiece({move.startIndex, move.startIndex + 2, 0});
                movePiece({move.startIndex + 4, move.startIndex + 1, 0});
            }
        }
        return;
    }

    for(int i = 0; i < 16; i++){
        clearBit(boardFlags[i], move.targetIndex);

        if(hasBit(boardFlags[i], move.startIndex)){
            clearBit(boardFlags[i], move.startIndex);
            setBit(boardFlags[i], move.targetIndex);
            clearBit(boardFlags[15], move.startIndex);
            clearBit(boardFlags[15], move.targetIndex);
        }
    }

    *boardFlags[13] = 0;
    for(int i = 1; i < 7; i++){
        *boardFlags[13] |= *boardFlags[i];
    }

    *boardFlags[14] = 0;
    for(int i = 7; i < 13; i++){
        *boardFlags[14] |= *boardFlags[i];
    }
}

bool Board::isAttacked(int index, int team){
    ////cout << "Team: " << team << " Index: " << index << "\n";
    vector<int> attackingPieces;

    if(team == 0){
        for(int i = 0; i < 64; i++){
            if(hasBit(boardFlags[14], i)){
                attackingPieces.push_back(i);
            }   
        }
    } else if (team == 1){
        for(int i = 0; i < 64; i++){
            if(hasBit(boardFlags[13], i)){
                attackingPieces.push_back(i);
            }
        }    
    }

    for(int i = 0; i < attackingPieces.size(); i++){
        vector<Move> possMoves = getPossMoves(attackingPieces[i], attacking);

        for(int i = 0; i < possMoves.size(); i++){
            if(possMoves[i].targetIndex == index)
                return true;
        }
    }

    return false;
}