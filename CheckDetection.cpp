#include "Board.hpp"

bool Board::isInCheck(int king){
    int kingPos;

    if(king == 0){
        for(int i = 0; i < 64; i++){
            if(*boardFlags[6] & (1ULL << i)){
                kingPos = i;
                break;
            }
        }

        for(int i = 0; i < 64; i++){
            if(*boardFlags[14] & (1ULL << i)){
                vector<Move> currPossMoves = getPossMoves(i, attacking);

                for(int x = 0; x < currPossMoves.size(); x++){
                    if(currPossMoves[x].targetIndex == kingPos){
                        return true;
                    }
                }
            }
        }
    } else if(king == 1){
        for(int i = 0; i < 64; i++){
            if(*boardFlags[12] & (1ULL << i)){
                kingPos = i;
                break;
            }
        }

        for(int i = 0; i < 64; i++){
            if(*boardFlags[13] & (1ULL << i)){
                vector<Move> currPossMoves = getPossMoves(i, attacking);

                for(int x = 0; x < currPossMoves.size(); x++){
                    if(currPossMoves[x].targetIndex == kingPos){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Board::isCheckMate(int king){
    uint64_t team = king == 0 ? *boardFlags[13] : *boardFlags[14];

    for(int i = 0; i < 64; i++){
        if(hasBit(&team, i)){
            vector<Move> possMoves = getPossMoves(i, regular);

            for(int j = 0; j < possMoves.size(); j++){
                Board tempBoard(*this);
                tempBoard.movePiece(possMoves[i]);
                if(!tempBoard.isInCheck(king))
                    return false;
            }
        }
    }

    return true;
}