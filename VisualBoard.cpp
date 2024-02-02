#include "Board.hpp"
#include "Utilities.hpp"
#include "VisualBoard.hpp"
#include <cmath>
#include <iostream>

VisualBoard::VisualBoard(int layout[][8]) : Board(layout){
    pieceVisuals = getSprites();
    newArrow = new Vector2i(-1, -1);
    head = nullptr;
    createBoard();
    createPieces();
}

void VisualBoard::reset(){
    for(int i = 0; i < sizeof(boardFlags) / sizeof(uint64_t); i++)
        **(boardFlags + i) = 0;
    setBoard(standard1);
    createPieces();
}

vector<Sprite> VisualBoard::getSprites(){
    vector<Sprite> Sprites;

    for(int i = 0; i < 12; i++){
        string filePath = "../../Pieces/" + pieceNames[i] + ".png";

        pieceTextures[i].loadFromFile(filePath);

        Sprite sprite(pieceTextures[i]);
        sprite.setScale(squareSize / sprite.getLocalBounds().width, squareSize / sprite.getLocalBounds().height);

        Sprites.push_back(sprite);
    }

    return Sprites;
}

void VisualBoard::createBoard(){
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            RectangleShape rect(Vector2f(squareSize, squareSize));
            rect.setPosition(x * squareSize, y * squareSize);

            switch ((x + y) % 2){
                case 0:
                    rect.setFillColor(Light);
                    gridSquares[x][y] = {rect, nullptr, x, y, false, false, Light, LightHighlight, LightMarked};
                    break;
                
                case 1:
                    rect.setFillColor(Dark);
                    gridSquares[x][y] = {rect, nullptr, x, y, false, false, Dark, DarkHighlight, DarkMarked};
                    break;
            }
        }
    }
}

void VisualBoard::createPieces(){
    int pieceNum = 0;
    for(int i = 0; i < sizeof(pieces) / sizeof(pieces[0]); i++){
        pieces[i].alive = false;
    }

    for(int i = 1; i < 13; i++){
        for(int j = 0; j < 64; j++){
            int x = getX(j);
            int y = getY(j);

            //gridSquares[x][y].piece = nullptr;

            if(*boardFlags[i] & 1ULL << j){
                pieces[pieceNum] = {pieceVisuals[i - 1], x, y};
                pieces[pieceNum].visual.setPosition(x * squareSize, y * squareSize);
                gridSquares[x][y].piece = &pieces[pieceNum];
                pieceNum++;
            }
        }
    }
}

void VisualBoard::movePiece(Move move){
    /*Vector2i startCoords(startSquare->x, startSquare->y);
    Vector2i targetCoords(targetSquare->x, targetSquare->y);
    int startIndex = (7 - startCoords.x) + ((7 - startCoords.y) * 8);
    int targetIndex = (7 - targetCoords.x) + ((7 - targetCoords.y) * 8);*/

    Board::movePiece(move);

    createPieces();

    //cout << (getTeam(move.targetIndex) == 0 ? 1 : 0) << ", " << isCheckMate(getTeam(move.targetIndex) == 0 ? 1 : 0) << "\n";
    /*if(targetSquare->piece != nullptr)
        targetSquare->piece->alive = false;

    startSquare->piece->x = targetSquare->x;
    startSquare->piece->y = targetSquare->y;
    targetSquare->piece = startSquare->piece;
    startSquare->piece = nullptr;*/

    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            gridSquares[x][y].isMarked = false;
        }
    }

    Arrow* curr = head;

    while(curr != nullptr){
        Arrow* next = curr->next;
        delete curr;
        curr = next;
    }

    head = nullptr;
}

bool VisualBoard::checkedMove(Move move){
    /*Vector2i startCoords(startSquare->x, startSquare->y);
    Vector2i targetCoords(targetSquare->x, targetSquare->y);
    int startIndex = (7 - startCoords.x) + ((7 - startCoords.y) * 8);
    int targetIndex = (7 - targetCoords.x) + ((7 - targetCoords.y) * 8);*/

    int team = hasBit(boardFlags[13], move.startIndex) ? 0 : 1;

    //if()

    vector<Move> possMoves = getPossMoves(move.startIndex, regular);
    for(int i = 0; i < possMoves.size(); i++){
        if(move.targetIndex == possMoves[i].targetIndex){
            movePiece(possMoves[i]);
            return true;
            break;
        }
    }

    return false;
}

void VisualBoard::draw(RenderWindow& window){
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(gridSquares[x][y].isMarked){
                gridSquares[x][y].visual.setFillColor(gridSquares[x][y].markedColor);
            } else {
                gridSquares[x][y].visual.setFillColor(gridSquares[x][y].origColor);
            }

            if(gridSquares[x][y].isHighlighted){
                gridSquares[x][y].visual.setFillColor(gridSquares[x][y].highColor);
            }
            
            window.draw(gridSquares[x][y].visual);

            if(gridSquares[x][y].piece != nullptr && gridSquares[x][y].piece->alive){
                if(!gridSquares[x][y].piece->isDragged)
                    gridSquares[x][y].piece->visual.setPosition(gridSquares[x][y].piece->x * squareSize, gridSquares[x][y].piece->y * squareSize);

                if(&gridSquares[x][y] != selectedSquare)
                    window.draw(gridSquares[x][y].piece->visual);
            }

        }
    }

    if(selectedSquare != nullptr){
        if(selectedSquare->piece->isDragged){
            selectedSquare->piece->visual.setPosition(selectedSquare->piece->locX * squareSize - 50, selectedSquare->piece->locY * squareSize - 50);
        } else {
            selectedSquare->piece->visual.setPosition(selectedSquare->piece->x * squareSize, selectedSquare->piece->y * squareSize);
        }
        window.draw(selectedSquare->piece->visual);
    }

    Arrow* curr = head;
    Arrow* last = nullptr;

    if(head == nullptr && newArrow->x != newArrow->y){
        head = new Arrow(newArrow->x, newArrow->y);
        newArrow->x = -1;
        newArrow->y = -1;
    }

    while (curr != nullptr) {
        if(curr->startSq != newArrow->x || curr->endSq != newArrow->y){
            window.draw(*curr->body);
            window.draw(*curr->head);

            if(curr->next == nullptr && newArrow->x != newArrow->y){
                curr->next = new Arrow(newArrow->x, newArrow->y);
                newArrow->x = -1;
                newArrow->y = -1;
            }
            last = curr;
            curr = curr->next;
        } else {
            if(head == curr){
                head = head->next;
                last = curr;
                curr = curr->next;
                delete last;
                newArrow->x = -1;
                newArrow->y = -1;
            } else if(curr->next != nullptr){
                last->next = curr->next;
                delete curr;
                curr = last->next;
                newArrow->x = -1;
                newArrow->y = -1;
            } else if(curr->next == nullptr){
                last->next = nullptr;
                delete curr;
                curr = nullptr;
                newArrow->x = -1;
                newArrow->y = -1;
            }
        }
    }
}

void VisualBoard::highPossMoves(Square* square){
    Vector2i squareCoords(square->x, square->y);
    int pieceIndex = (7 - squareCoords.x) + ((7 - squareCoords.y) * 8);

    vector<Move> possMoves = getPossMoves(pieceIndex, regular);

    for(int i = 0; i < possMoves.size(); i++){
        int targetX = getX(possMoves[i].targetIndex);
        int targetY = getY(possMoves[i].targetIndex);

        gridSquares[targetX][targetY].isHighlighted = true;
    }
}

void VisualBoard::unHighlight(){
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            gridSquares[x][y].isHighlighted = false;
        }
    }
}

void VisualBoard::addArrow(int startSq, int endSq){
    newArrow->x = startSq;
    newArrow->y = endSq;
}