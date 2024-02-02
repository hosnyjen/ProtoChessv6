#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int windowWidth = 800;
const int windowLength = 800;

const int squareSize = 100;

const Color Light(237,214,176);
const Color LightHighlight(237,250,176);
const Color Dark(184,135,98);
const Color DarkHighlight(184,250,98);

string pieceNames[] = {
    "wPawn", "wKnight", "wBishop", "wRook", "wQueen", "wKing",
    "bPawn", "bKnight", "bBishop", "bRook", "bQueen", "bKing"
};

string flagNames[] = {
    "occupied",
    "wPawn", "wKnight", "wBishop", "wRook", "wQueen", "wKing",
    "bPawn", "bKnight", "bBishop", "bRook", "bQueen", "bKing",
    "wPieces", "bPieces", "noMoves"
};

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

int standard1[8][8] = {
    {-4, -2, -3, -5, -6, -3, -2, -4},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 1,  1,  1,  1,  1,  1,  1,  1},
    { 4,  2,  3,  5,  6,  3,  2,  4}
};