#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

const int windowWidth = 800;
const int windowLength = 800;
const int squareSize = 100;

//Special Moves
const int castling = 64;
const int queenPromote = 32;
const int rookPromote = 16;
const int bishopPromote = 8;
const int knightPromote = 4;
const int enPassant = 2;
const int doubleMove = 1;

//Search Types
const int special = 8;
const int regular = 4;
const int attacking = 2;

/*const int raw = 8;
const int special = 4;
const int attacking = 2;
const int passive = 1;*/

const Color Light(237,214,176);
const Color LightHighlight(237,250,176);
const Color LightMarked(235,121,99);
const Color Dark(184,135,98);
const Color DarkHighlight(184,250,98);
const Color DarkMarked(225,105,84);

extern string pieceNames[12];

extern string flagNames[16];

struct Piece {
    Sprite visual;
    int x;
    int y;
    double locX;
    double locY;
    bool isDragged;
    bool alive = true;
};

struct Square {
    RectangleShape visual;
    Piece* piece;
    int x;
    int y;
    bool isHighlighted;
    bool isMarked;
    Color origColor;
    Color highColor;
    Color markedColor;
};

struct Move {
    int startIndex;
    int targetIndex;
    int specialType;
};

extern int standard1[8][8];