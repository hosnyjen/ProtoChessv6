#include "Board.hpp"
#include "Utilities.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

vector<Move> Board::getPossMoves(int pieceIndex, int searchType){
    //cout << pieceIndex << "\n";
    vector<Move> moves = {};
    bool pieceType[12] = {false};

    ////cout << "SearchType: " << searchType << "\n";

    for(int i = 1; i < 13; i++){
        if(hasBit(boardFlags[i], pieceIndex)){
            pieceType[i - 1] = true;
        }
    }

    if(pieceType[0] || pieceType[6]){
        //cout << "Pawn\n";
        int moveDir = pieceType[0] ? 1 : -1;
        int promotionRank = pieceType[0] ? 7 : 0;

        bool (Board::*isOther)(int);
        isOther = (pieceType[0]) ? &Board::isBlack : &Board::isWhite;

        if(searchType != special && pieceIndex + (8 * moveDir) <= 63 && !isOccupied(pieceIndex + (8 * moveDir))){
            ////cout << "hi\n";
            if(pieceIndex / 8 == promotionRank - 1)
                moves.push_back({pieceIndex, pieceIndex + (8 * moveDir), queenPromote});
            else
                moves.push_back({pieceIndex, pieceIndex + (8 * moveDir), 0});
            if(searchType != special && pieceIndex + (16 * moveDir) <= 63 && !isOccupied(pieceIndex + (16 * moveDir)) && hasBit(boardFlags[15], pieceIndex)){
                moves.push_back({pieceIndex, pieceIndex + (16 * moveDir), doubleMove});
            }
        }

        if(searchType != special && hasBit(boardFlags[16], pieceIndex) && hasBit(boardFlags[17], pieceIndex - (1 * moveDir)) && (this->*isOther)(pieceIndex - (1 * moveDir))){
            //cout << "hi1\n";
            moves.push_back({pieceIndex, pieceIndex + (7 * moveDir), enPassant});
        } else if((searchType != special && pieceIndex + (7 * moveDir) <= 63 && pieceIndex % 8 > 0 && (this->*isOther)(pieceIndex + (7 * moveDir))) || searchType == attacking){
            if(pieceIndex / 8 == promotionRank - 1)
                moves.push_back({pieceIndex, pieceIndex + (7 * moveDir), queenPromote});
            else
                moves.push_back({pieceIndex, pieceIndex + (7 * moveDir), 0});
        }
        if(hasBit(boardFlags[16], pieceIndex) && hasBit(boardFlags[17], pieceIndex + (1 * moveDir)) && (this->*isOther)(pieceIndex + (1 * moveDir))){
            ////cout << "hi2\n";
            moves.push_back({pieceIndex, pieceIndex + (9 * moveDir), enPassant});
        } else if((pieceIndex + (9 * moveDir) <= 63 && pieceIndex % 8 < 7 && (this->*isOther)(pieceIndex + (9 * moveDir))) || searchType == attacking){
            if(pieceIndex / 8 == promotionRank - 1)
                moves.push_back({pieceIndex, pieceIndex + (9 * moveDir), queenPromote});
            else
                moves.push_back({pieceIndex, pieceIndex + (9 * moveDir), 0});
        }/**/
    } else if(pieceType[1] || pieceType[7]){
        ////cout << "Knight\n";
        bool (Board::*isOther)(int);
        isOther = (pieceType[1]) ? &Board::isBlack : &Board::isWhite;

        if((searchType == regular || searchType == attacking)){
            if(pieceIndex % 8 > 0 && pieceIndex / 8 < 6 && pieceIndex + 15 <= 63 && (!(*boardFlags[0] & (1ULL << pieceIndex + 15)) || (this->*isOther)(pieceIndex + 15))){
                moves.push_back({pieceIndex, pieceIndex + 15, 0});
            }

            if(pieceIndex % 8 > 1 && pieceIndex / 8 < 7 && pieceIndex + 6 <= 63 && (!(*boardFlags[0] & (1ULL << pieceIndex + 6)) || (this->*isOther)(pieceIndex + 6))){
                moves.push_back({pieceIndex, pieceIndex + 6, 0});
            }

            if(pieceIndex % 8 > 1 && pieceIndex / 8 > 0 && pieceIndex - 10 >= 0 && (!(*boardFlags[0] & (1ULL << pieceIndex - 10)) || (this->*isOther)(pieceIndex - 10))){
                moves.push_back({pieceIndex, pieceIndex - 10, 0});
            }

            if(pieceIndex % 8 > 0 && pieceIndex / 8 > 1 && pieceIndex - 17 >= 0 && (!(*boardFlags[0] & (1ULL << pieceIndex - 17)) || (this->*isOther)(pieceIndex - 17))){
                moves.push_back({pieceIndex, pieceIndex - 17, 0});
            }

            if(pieceIndex % 8 < 7 && pieceIndex / 8 > 1 && pieceIndex - 15 >= 0 && (!(*boardFlags[0] & (1ULL << pieceIndex - 15)) || (this->*isOther)(pieceIndex - 15))){
                moves.push_back({pieceIndex, pieceIndex - 15, 0});
            }

            if(pieceIndex % 8 < 6 && pieceIndex / 8 > 0 && pieceIndex - 6 >= 0 && (!(*boardFlags[0] & (1ULL << pieceIndex - 6)) || (this->*isOther)(pieceIndex - 6))){
                moves.push_back({pieceIndex, pieceIndex - 6, 0});
            }

            if(pieceIndex % 8 < 6 && pieceIndex / 8 < 7 && pieceIndex + 10 <= 63 && (!(*boardFlags[0] & (1ULL << pieceIndex + 10)) || (this->*isOther)(pieceIndex + 10))){
                moves.push_back({pieceIndex, pieceIndex + 10, 0});
            }

            if(pieceIndex % 8 < 7 && pieceIndex / 8 < 6 && pieceIndex + 17 <= 63 && (!(*boardFlags[0] & (1ULL << pieceIndex + 17)) || (this->*isOther)(pieceIndex + 17))){
                moves.push_back({pieceIndex, pieceIndex + 17, 0});
            }
        }
    } else if(pieceType[2] || pieceType[8]){
        //cout << "Bishop\n";
        bool (Board::*isOther)(int);
        isOther = (pieceType[2]) ? &Board::isBlack : &Board::isWhite;

        if((searchType == regular || searchType == attacking)){
            for(int i = 7; i < 64; i += 7){
                if(pieceIndex % 8 == 0 || pieceIndex / 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) % 8 == 0 || (pieceIndex + i) / 8 == 7){
                    break;
                }
            }

            for(int i = 9; i < 64; i += 9){
                if(pieceIndex % 8 == 7 || pieceIndex / 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) % 8 == 7 || (pieceIndex + i) / 8 == 7){
                    break;
                }
            }

            for(int i = 7; i < 64; i += 7){
                if(pieceIndex % 8 == 7 || pieceIndex / 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex- i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex- i, 0});
                if((pieceIndex - i) % 8 == 7 || (pieceIndex - i) / 8 == 0){
                    break;
                }
            }

            for(int i = 9; i < 64; i += 9){
                if(pieceIndex % 8 == 0 || pieceIndex / 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex- i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex- i, 0});
                if((pieceIndex - i) % 8 == 0 || (pieceIndex - i) / 8 == 0){
                    break;
                }
            }
        }
    } else if(pieceType[3] || pieceType[9]){
        //cout << "Rook\n";
        bool (Board::*isOther)(int);
        isOther = (pieceType[3]) ? &Board::isBlack : &Board::isWhite;

        if((searchType == regular || searchType == attacking)){
            for(int i = 8; i < 64; i += 8){
                if(pieceIndex / 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) / 8 == 7){
                    break;
                }
            }

            for(int i = 1; i < 64; i += 1){
                if(pieceIndex % 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) % 8 == 7){
                    break;
                }
            }

            for(int i = 8; i < 64; i += 8){
                if(pieceIndex / 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex - i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex - i, 0});
                if((pieceIndex - i) / 8 == 0){
                    break;
                }
            }

            for(int i = 1; i < 64; i += 1){
                if(pieceIndex % 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex - i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex - i, 0});
                if((pieceIndex - i) % 8 == 0){
                    break;
                }
            }
        }
    } else if(pieceType[4] || pieceType[10]){
        //cout << "Queen\n";
        bool (Board::*isOther)(int);
        isOther = (pieceType[4]) ? &Board::isBlack : &Board::isWhite;

        if((searchType == regular || searchType == attacking)){
            for(int i = 7; i < 64; i += 7){
                if(pieceIndex % 8 == 0 || pieceIndex / 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) % 8 == 0 || (pieceIndex + i) / 8 == 7){
                    break;
                }
            }

            for(int i = 9; i < 64; i += 9){
                if(pieceIndex % 8 == 7 || pieceIndex / 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) % 8 == 7 || (pieceIndex + i) / 8 == 7){
                    break;
                }
            }

            for(int i = 7; i < 64; i += 7){
                if(pieceIndex % 8 == 7 || pieceIndex / 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex - i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex - i, 0});
                if((pieceIndex - i) % 8 == 7 || (pieceIndex - i) / 8 == 0){
                    break;
                }
            }

            for(int i = 9; i < 64; i += 9){
                if(pieceIndex % 8 == 0 || pieceIndex / 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex - i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex - i, 0});
                if((pieceIndex - i) % 8 == 0 || (pieceIndex - i) / 8 == 0){
                    break;
                }
            }

            for(int i = 8; i < 64; i += 8){
                if(pieceIndex / 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) / 8 == 7){
                    break;
                }
            }

            for(int i = 1; i < 64; i += 1){
                if(pieceIndex % 8 == 7){
                    break;
                }
                if(pieceIndex + i > 63){
                    break;
                }
                if((this->*isOther)(pieceIndex + i)){
                    moves.push_back({pieceIndex, pieceIndex + i, 0});
                    break;
                }
                if(isOccupied(pieceIndex + i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex + i, 0});
                if((pieceIndex + i) % 8 == 7){
                    break;
                }
            }

            for(int i = 8; i < 64; i += 8){
                if(pieceIndex / 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex - i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex - i, 0});
                if((pieceIndex - i) / 8 == 0){
                    break;
                }
            }

            for(int i = 1; i < 64; i += 1){
                if(pieceIndex % 8 == 0){
                    break;
                }
                if(pieceIndex - i < 0){
                    break;
                }
                if((this->*isOther)(pieceIndex - i)){
                    moves.push_back({pieceIndex, pieceIndex - i, 0});
                    break;
                }
                if(isOccupied(pieceIndex - i)){
                    break;
                }
                moves.push_back({pieceIndex, pieceIndex - i, 0});
                if((pieceIndex - i) % 8 == 0){
                    break;
                }
            }
        }
    } else if(pieceType[5] || pieceType[11]){
        //cout << "King\n";
        bool (Board::*isOther)(int);
        isOther = (pieceType[5]) ? &Board::isBlack : &Board::isWhite;

        if(searchType == attacking){
            if(pieceIndex % 8 != 0 && pieceIndex - 1 >= 0){
                moves.push_back({pieceIndex, pieceIndex - 1, 0});
            }
            if(!(pieceIndex % 8 == 0 || pieceIndex / 8 == 0)){
                moves.push_back({pieceIndex, pieceIndex - 9, 0});
            }
            if(pieceIndex / 8 != 0 && pieceIndex - 8 >= 0){
                moves.push_back({pieceIndex, pieceIndex - 8, 0});
            }
            if(!(pieceIndex % 8 == 7 || pieceIndex / 8 == 0)){
                moves.push_back({pieceIndex, pieceIndex - 7, 0});
            }
            if(pieceIndex % 8 != 7 && pieceIndex + 1 <= 63){
                moves.push_back({pieceIndex, pieceIndex + 1, 0});
            }
            if(!(pieceIndex % 8 == 7 || pieceIndex / 8 == 7)){
                moves.push_back({pieceIndex, pieceIndex + 9, 0});
            }
            if(pieceIndex / 8 != 7 && pieceIndex + 8 <= 63){
                moves.push_back({pieceIndex, pieceIndex + 8, 0});
            }
            if(!(pieceIndex % 8 == 0 || pieceIndex / 8 == 7)){
                moves.push_back({pieceIndex, pieceIndex + 7, 0});
            }
        } else {
            if(pieceIndex % 8 != 0 && pieceIndex - 1 >= 0 && (!isOccupied(pieceIndex - 1) || (this->*isOther)(pieceIndex - 1)) && !isAttacked(pieceIndex - 1, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex - 1, 0});
            }
            if(!(pieceIndex % 8 == 0 || pieceIndex / 8 == 0) && pieceIndex - 9 >= 0 && (!isOccupied(pieceIndex - 9) || (this->*isOther)(pieceIndex - 9)) && !isAttacked(pieceIndex - 9, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex - 9, 0});
            }
            if(pieceIndex / 8 != 0 && pieceIndex - 8 >= 0 && (!isOccupied(pieceIndex - 8) || (this->*isOther)(pieceIndex - 8)) && !isAttacked(pieceIndex - 8, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex - 8, 0});
            }
            if(!(pieceIndex % 8 == 7 || pieceIndex / 8 == 0) && pieceIndex - 7 >= 0 && (!isOccupied(pieceIndex - 7) || (this->*isOther)(pieceIndex - 7)) && !isAttacked(pieceIndex - 7, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex - 7, 0});
            }
            if(pieceIndex % 8 != 7 && pieceIndex + 1 <= 63 && (!isOccupied(pieceIndex + 1) || (this->*isOther)(pieceIndex + 1)) && !isAttacked(pieceIndex + 1, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex + 1, 0});
            }
            if(!(pieceIndex % 8 == 7 || pieceIndex / 8 == 7) && pieceIndex + 9 <= 63 && (!isOccupied(pieceIndex + 9) || (this->*isOther)(pieceIndex + 9)) && !isAttacked(pieceIndex + 9, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex + 9, 0});
            }
            if(pieceIndex / 8 != 7 && pieceIndex + 8 <= 63 && (!isOccupied(pieceIndex + 8) || (this->*isOther)(pieceIndex + 8)) && !isAttacked(pieceIndex + 8, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex + 8, 0});
            }
            if(!(pieceIndex % 8 == 0 || pieceIndex / 8 == 7) && pieceIndex + 7 <= 63 && (!isOccupied(pieceIndex + 7) || (this->*isOther)(pieceIndex + 7)) && !isAttacked(pieceIndex + 7, getTeam(pieceIndex))){
                moves.push_back({pieceIndex, pieceIndex + 7, 0});
            }
        }

        if(searchType == regular || searchType == special){
            if(!isOccupied(pieceIndex - 1) && !isOccupied(pieceIndex - 2) && hasBit(boardFlags[15], pieceIndex)){
                if(!isAttacked(pieceIndex - 1, getTeam(pieceIndex)) && !isAttacked(pieceIndex - 2, getTeam(pieceIndex)) && hasBit(boardFlags[15], pieceIndex - 3)){
                    moves.push_back({pieceIndex, pieceIndex - 2, castling});
                    moves.push_back({pieceIndex, pieceIndex - 3, castling});
                }
            }
            if(!isOccupied(pieceIndex + 1) && !isOccupied(pieceIndex + 2) && !isOccupied(pieceIndex + 3) && hasBit(boardFlags[15], pieceIndex)){
                if(!isAttacked(pieceIndex + 1, getTeam(pieceIndex)) && !isAttacked(pieceIndex + 2, getTeam(pieceIndex)) && !isAttacked(pieceIndex + 3, getTeam(pieceIndex)) && hasBit(boardFlags[15], pieceIndex + 4)){
                    moves.push_back({pieceIndex, pieceIndex + 2, castling});
                    moves.push_back({pieceIndex, pieceIndex + 4, castling});
                }
            }
        }
    }
    if(searchType == regular){
        vector<Move> validatedMoves;
        for(int i = 0; i < moves.size(); i++){
            int team = getTeam(moves[i].startIndex);
            Board tempBoard(*this);
            tempBoard.movePiece(moves[i]);

            if(!tempBoard.isInCheck(team)){
                validatedMoves.push_back(moves[i]);
                //cout << "true\n";
            }
        }
        moves = validatedMoves;
    }/**/
    for(int i = 0; i < moves.size(); i++){
        //cout << moves[i].startIndex << "," << moves[i].targetIndex << "," << moves[i].specialType << "\n";
    }
    return moves;
}