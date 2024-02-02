#pragma once

#include "Utilities.hpp"
#include "Arrow.hpp"
#include "Board.hpp"

class VisualBoard: public Board {
    public:
        Square gridSquares[8][8];
        Piece pieces[32];
        Square* selectedSquare;

        vector<Sprite> pieceVisuals;
        Texture pieceTextures[12];
        Vector2i* newArrow;
        Arrow* head;

    public:
        VisualBoard(int layout[][8]);

        void reset();

        vector<Sprite> getSprites();

        void createBoard();

        void createPieces();

        void movePiece(Move move);

        bool checkedMove(Move move);

        void draw(RenderWindow& window);

        void highPossMoves(Square* square);

        void unHighlight();

        void addArrow(int startSq, int endSq);
};